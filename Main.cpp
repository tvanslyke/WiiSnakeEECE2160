/*
 * Main.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: tim
 */

#include "SnakeGame.h"
#include <cstdlib>


int main(int argc, char *argv[])
{
	size_t width = 64;
	size_t height = 32;
	if(argc > 2)
	{
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}
	try
	{
		SnakeGame snake_game(width, height, false);
		snake_game.run();
	}
	catch(std::exception & game_over)
	{
		std::cout << game_over.what() << std::endl;
	}
	return 0;
}
