/*
 * RandomNumbers.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOMNUMBERS_H_
#define RANDOMNUMBERS_H_
#include <type_traits>
#include "BaseRNG.h"
#include <iostream>
#include <stdexcept>


namespace rng{

/**
 * Bounded-range random number generator.
 */
template<typename T>
class UniformRNG
{
private:
	using Dist = typename std::conditional<std::is_integral<T>::value,
			                               std::uniform_int_distribution<T>,
										   std::uniform_real_distribution<T>>::type;
	Dist dist_;
public:
	UniformRNG():UniformRNG<T>(T(0), T(0)){}

	/**
	 * Create a new UniformRNG for an integral type.
	 */
	UniformRNG(T lb, T ub)
	{
		if(lb > ub)
		{
			throw std::invalid_argument("Provided lower bound (" + std::to_string(lb) +
					") is greater than the provided upper bound ("  + std::to_string(ub) + ").");
		}
		dist_ = Dist(lb, ub);
	}
	/**
	 * Create a new UniformRNG for an integral type from a std::pair.
	 */
	UniformRNG(std::pair<T, T> lims)
	{
		assert(lims.first <= lims.second);
		dist_ = Dist(lims.first, lims.second);
	}

	/**
	 * Create a new random integer.  Identical to operator().
	 */
	T getRandomNumber()
	{
		return this->dist_(BaseRNG::twister_);
	}


	/**
	 * Create a new random integer.  Identical to getRandomNumber().
	 * @return the new random integer.
	 */
	T operator()()
	{
		return this->dist_(BaseRNG::twister_);
	}

	T max()
	{
		return dist_.max();
	}
	T min()
	{
		return dist_.min();
	}
	void setMax(T newMax)
	{
		dist_.param(typename Dist::param_type(min(), newMax));
	}
	void setMin(T newMin)
	{
		dist_.param(typename Dist::param_type(newMin, max()));
	}
	void setBounds(T lb, T ub)
	{
		dist_.param(typename Dist::param_type(lb, ub));
	}
	void setBounds(const std::pair<T, T> & bounds)
	{
		dist_.param(typename Dist::param_type(bounds.first, bounds.second));
	}
};


}

#endif /* RANDOMNUMBERS_H_ */
