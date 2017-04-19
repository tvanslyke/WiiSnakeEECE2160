/*
 * BaseRNG.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#include "BaseRNG.h"
#include <random>

namespace rng{


BaseRNG::BaseRNG(){}


uint_fast64_t BaseRNG::getRandomNumber() noexcept
{
	return twister_();
}
unsigned int BaseRNG::getVeryRandomNumber()
{
	return rd_();
}


// instantiate random engines

std::random_device BaseRNG::rd_;
std::mt19937_64 BaseRNG::twister_(BaseRNG::rd_());

}
