/*
 * SnakeGame.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: tim
 */

#include "SnakeGame.h"
#include "WiiMote.h"
#include "KeyBoard.h"
#include <thread>
using namespace std::chrono;
SnakeGame::SnakeGame(size_t board_width, size_t board_height, bool use_wiimote):
	snake_board(board_width, board_height), dir_mutex(), frame_delay(200), paused(false)
{
	if(use_wiimote)
		input_device = std::unique_ptr<EventReader>(new wii::WiiMote());
	else
			input_device = std::unique_ptr<EventReader>(new KeyBoard());
	direction = 1;
	direction_save = 1;
	std::function<void(int)> arrow_action = [this](int code)->void
	{
		if(not this->paused)
		{
			auto new_dir = (char(code) >> 1) & 0x03;
			new_dir ^= ((new_dir >> 1) & 0x01);
			Lock lock(this->dir_mutex);
			if(new_dir != (direction_save ^ 0x01))
			{
				this->direction = new_dir;
			}
		}
	};
	input_device->setEventAction(wii::UP, arrow_action);
	input_device->setEventAction(wii::DOWN, arrow_action);
	input_device->setEventAction(wii::LEFT, arrow_action);
	input_device->setEventAction(wii::RIGHT, arrow_action);
	std::function<void(int)> home_action = [this](int code)->void
	{
		Lock lock(pause_mutex);
		this->paused = not this->paused;
	};
	input_device->setEventAction(wii::HOME, home_action);
	std::function<void(int)> plus_action = [this](int code)->void
	{
		if(this->frame_delay > Millis(0))
		{
			Lock lock(delay_mutex);
			this->frame_delay -= Millis(20);
		}
	};
	std::function<void(int)> minus_action = [this](int code)->void
	{
		if(this->frame_delay < Millis(1000))
		{
			Lock lock(delay_mutex);
			this->paused = not this->paused;
			this->frame_delay += Millis(20);
		}
	};
	input_device->setEventAction(wii::PLUS, plus_action);
	input_device->setEventAction(wii::A, plus_action);
	input_device->setEventAction(wii::MINUS, minus_action);
	input_device->setEventAction(wii::B, minus_action);
}
void SnakeGame::run()
{
	try
	{
		auto run_input_device = [this]()->void
		{
			this->runInputDevice();
		};
		auto run_snake = [this]()->void
		{
			this->runSnake();
		};
		std::cout << "Starting Game" << std::endl;
		std::thread input_thread(run_input_device);
		std::thread game_thread(run_snake);
		input_thread.join();
		game_thread.join();
	}
	catch(game_over_exception & game_over)
	{
		std::cout << "Game over!" << std::endl;
		std::cout << "Total Length: " << snake_board.snakeSize() << std::endl;
	}

}
void SnakeGame::runInputDevice()
{
	while(true)
	{
		input_device->checkEvent();
	}
}
void SnakeGame::runSnake()
{
	char local_direction_copy = 0;
	auto start = steady_clock::now();
	auto sleep_duration = Millis(0);
	bool local_paused_copy = false;

	while(true)
	{
		{
			Lock lock(pause_mutex);
			local_paused_copy = paused;
		}
		while(not local_paused_copy)
		{
			{
				Lock lock(delay_mutex);
				sleep_duration = frame_delay - duration_cast<Millis>(steady_clock::now() - start);
			}
			if(sleep_duration > Millis(0))
				std::this_thread::sleep_for(sleep_duration);
			{
				Lock lock(dir_mutex);
				local_direction_copy = direction;
				direction_save = direction;
			}
			start = steady_clock::now();
			snake_board.update(local_direction_copy);
			{
				Lock lock(pause_mutex);
				local_paused_copy = paused;
			}
		}
	}
}
