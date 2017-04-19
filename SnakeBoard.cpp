/*
 * SnakeBoard.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: tim
 */

#include "SnakeBoard.h"





SnakeBoard::SnakeBoard(size_t width, size_t height):
	board_width(width),
	board_height(height),
	total_slots(width * height),
	gen(0, total_slots - 1 ),
	open_slots(),
	snake()
{
	board.resize(board_height);
	border.resize(board_width + 2, BORDER_CHAR);
	flush.resize(FLUSH_LINES, '\n');
	for(auto i = 0u; i < board_height; ++i)
	{
		board[i].resize(board_width, ' ');
	}
	board[0][0] = '#';
	board[0][1] = '#';
	generateFood();
}

void SnakeBoard::lazilyGenerateFood()
{

	size_t select = gen();
	size_t ypos = select / board_width;
	size_t xpos = select - ypos * board_width;
	while(board[ypos][xpos] == '#')
	{
		select = gen();
		ypos = select / board_width;
		xpos = select - ypos * board_width;
	}
	board[ypos][xpos] = 'o';
}
void SnakeBoard::carefullyGenerateFood()
{
	gen.setMax(total_slots - snake.size());
	auto begin = open_slots.begin();
	std::advance(begin, gen());
	*(*begin) = 'o';
}
void SnakeBoard::initializeOpenSlots()
{
	// placeholder slot so we can get a valid iterator from std::set::begin()
	open_slots.insert(nullptr);
	auto hint = open_slots.begin();
	for(auto & str:board)
	{
		hint = open_slots.begin();
		for(auto & chr:str)
		{
			if(chr == ' ')
			{
				hint = open_slots.emplace_hint(hint, &chr);
			}
		}
	}
	// remove the placeholder
	open_slots.erase(nullptr);
}

void SnakeBoard::generateFood()
{
	if(snake.size() < total_slots / 2)
	{
		lazilyGenerateFood();
	}
	else if(open_slots.size() == 0)
	{
		initializeOpenSlots();
	}
	else
	{
		carefullyGenerateFood();
	}
}
void SnakeBoard::update(char direction)
{
	std::cout << flush;
	std::cout << border << '\n';
	for(auto & str:board)
	{
		std::cout << BORDER_CHAR << str << BORDER_CHAR << '\n';
	}
	std::cout << border << std::endl;
	auto tail_pos = snake.getTailPosition();
	bool growth = snake.update(direction, board);
	if(snake.size() < total_slots / 2)
	{
		auto head_pos = snake.getHeadPosition();
		if(growth)
		{
			open_slots.erase(&(board[head_pos[1]][head_pos[1]]));
		}
		else
		{
			open_slots.erase(&(board[head_pos[1]][head_pos[1]]));
			open_slots.insert(&(board[tail_pos[1]][tail_pos[1]]));
		}
	}
	if(growth)
	{
		generateFood();
	}
}

size_t SnakeBoard::snakeSize() const noexcept
{
	return snake.size();
}
