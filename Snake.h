/*
 * Snake.h
 *
 *  Created on: Apr 15, 2017
 *      Author: tim
 */

#ifndef SNAKE_H_
#define SNAKE_H_
#include "Segment.h"
#include "Utilities.h"
#include <vector>
#include <iostream>
class Snake {
private:
	std::shared_ptr<Segment> head;
	std::shared_ptr<Segment> tail;
	size_t len;

public:
	Snake():
		head(std::make_shared<Segment>(1, 0, nullptr)),
		tail(std::make_shared<Segment>(0, 0, head)),
		len(2)
	{

	}
	std::array<size_t, 2> getHeadPosition() const
	{
		return head->getPosition();
	}
	std::array<size_t, 2> getTailPosition() const
	{
		return tail->getPosition();
	}
	bool update(char dir, std::vector<std::string> & board)
	{
		// up = 2; left = 0; right = 1; down = 3
		auto pos = head->getPosition();
		pos[get_bit<1>(dir)] += (signed)(get_bit<0>(dir) * 2) - 1;
		if(pos[1] >= board.size() or pos[1] < 0 or pos[0] >= board[0].size() or pos[0] < 0)
		{
			throw game_over_exception("You ran into a wall!\n");
			return false;
		}
		else
		{
			char & new_head_char = board[pos[1]][pos[0]];

			// game over if the snake is running into itself, except for the case
			// that it's running into its tail.
			if(new_head_char == '#' and not (pos[0] == tail->getX() and pos[1] == tail->getY()))
			{
				throw game_over_exception("You ran into yourself!\n");
				return false;
			}
			// growth
			else if(new_head_char == 'o')
			{
				new_head_char = '#';
				head->setNext(std::make_shared<Segment>(pos[0], pos[1], nullptr));
				head = head->getNext();
				++len;
				return true;
			}
			// no growth
			else
			{
				board[tail->getY()][tail->getX()] = ' ';
				new_head_char = '#';
				auto new_head = tail;
				tail = tail->getNext();
				new_head->setPosition(pos[0], pos[1]);
				head->setNext(new_head);
				head = new_head;
				return false;
			}
		}
	}
	template <class F>
	void apply(F & func) const
	{
		tail->apply(func);
	}
	size_t size() const noexcept
	{
		return len;
	}
};

#endif /* SNAKE_H_ */
