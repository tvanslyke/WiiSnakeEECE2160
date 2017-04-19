/*
 * Utilities.h
 *
 *  Created on: Apr 16, 2017
 *      Author: tim
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdexcept>
template <size_t N, typename T>
size_t get_bit(const T & integer)
{
	return (integer >> N) & 0x01;
}

class game_over_exception: public std::exception
{
private:
	std::string game_over_specifics;
public:
	game_over_exception(std::string specifics = "")
	{
		game_over_specifics = std::string("Game over!\n") + specifics;
	}
	const char * what() const noexcept
	{
		return game_over_specifics.c_str();
	}

};


#endif /* UTILITIES_H_ */
