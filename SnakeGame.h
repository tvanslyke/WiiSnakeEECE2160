/*
 * SnakeGame.h
 *
 *  Created on: Apr 16, 2017
 *      Author: tim
 */

#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_
#include "SnakeBoard.h"
#include "EventReader.h"
#include <mutex>
#include <chrono>
class SnakeGame {
private:
	using Millis = std::chrono::milliseconds;
	using Lock = std::lock_guard<std::mutex>;
	SnakeBoard snake_board;
	std::unique_ptr<EventReader> input_device;
	char direction;
	char direction_save;
	std::mutex dir_mutex;
	Millis frame_delay;
	std::mutex delay_mutex;
	bool paused;
	std::mutex pause_mutex;
public:
	SnakeGame(size_t board_width = 64, size_t board_height = 32, bool use_wiimote = true);
	void run();
	void runInputDevice();
	void runSnake();
};

#endif /* SNAKEGAME_H_ */
