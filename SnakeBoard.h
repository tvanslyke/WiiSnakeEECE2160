/*
 * SnakeBoard.h
 *
 *  Created on: Apr 15, 2017
 *      Author: tim
 */

#ifndef SNAKEBOARD_H_
#define SNAKEBOARD_H_
#include <vector>
#include <random>
#include <set>
#include <cassert>
#include <deque>
#include "UniformRNG.h"
#include "Snake.h"
#include <thread>
#include <mutex>
class SnakeBoard {
private:
	using Lock = std::lock_guard<std::mutex>;
	static constexpr const size_t FLUSH_LINES = 26;
	static const constexpr char BORDER_CHAR = 'x';
	const size_t board_width;
	const size_t board_height;
	const size_t total_slots;
	std::string border;
    std::string flush;
	rng::UniformRNG<size_t> gen;
	std::vector<std::string> board;
	std::set<char *> open_slots;
	Snake snake;

	void lazilyGenerateFood();
	void carefullyGenerateFood();
	void initializeOpenSlots();
	void generateFood();
public:
	SnakeBoard(size_t width, size_t height);

	void update(char direction);
	size_t snakeSize() const noexcept;
};

#endif /* SNAKEBOARD_H_ */
