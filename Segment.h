/*
 * Segment.h
 *
 *  Created on: Apr 15, 2017
 *      Author: tim
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <memory>
class Segment {
private:
	std::shared_ptr<Segment> next;
	size_t x;
	size_t y;
public:
	Segment(size_t xpos, size_t ypos): next(nullptr), x(xpos), y(ypos)
	{

	}
	Segment(size_t xpos, size_t ypos, std::shared_ptr<Segment> next_segment): next(next_segment), x(xpos), y(ypos)
	{

	}
	void apply(std::function<void(const Segment &)> func) const
	{
		func(*this);
		if(next)
		{
			next->apply(func);
		}
	}
	std::array<size_t, 2> getPosition() const
	{
		return {x, y};
	}
	void setPosition(size_t newx, size_t newy)
	{
		x = newx;
		y = newy;
	}
	size_t getX() const noexcept
	{
		return x;
	}
	size_t getY() const noexcept
	{
		return y;
	}
	std::shared_ptr<Segment> getNext()
	{
		return next;
	}
	void setNext(const std::shared_ptr<Segment> & new_next)
	{
		next = new_next;
	}
	void setNext(std::shared_ptr<Segment> && new_next)
	{
		next = std::move(new_next);
	}

};


#endif /* SEGMENT_H_ */
