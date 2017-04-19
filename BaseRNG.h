/*
 * RNGSeeder.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOM_BASERNG_H_
#define RANDOM_BASERNG_H_


#include <random>

namespace rng{

/**
 * Lightweight 'singleton' (entirely static so not exactly singleton)
 * An additional 64-bit Mersenne Twister object is housed to allow
 * UniformRNG and UniqueIntGenerator instances to all share the same
 * random engine.
 *
 * @author Timothy Van Slyke
 */
class BaseRNG
{

public:
	/**
	 * Get a random number from the internal std::mt19937_64.
	 * @return
	 */
	static uint_fast64_t getRandomNumber() noexcept;
	/**
	 * Get a random number from the internal std::random_device.
	 * @return
	 */
	static unsigned int getVeryRandomNumber();
	/**
	 * Maximum value that the std::mt19937_64 instance can generate.
	 * @return Maximum value that the std::mt19937_64 instance can generate.
	 */
	static constexpr uint_fast64_t max()
	{
		return std::mt19937_64::max();
	}
	/**
	 * Minimum value that the std::mt19937_64 instance can generate.
	 * @return Minimum value that the std::mt19937_64 instance can generate.
	 */
	static constexpr uint_fast64_t min()
	{
		return std::mt19937_64::min();
	}
	/**
	 * Difference between the maximum and minimum values that the
	 * std::mt19937_64 instance can generate.
	 * @return difference between max() and min().
	 */
	static constexpr uint_fast64_t range()
	{
		return max() - min();
	}
private:
	/** Random Device.  The 'randomest' of random number generators. */
	static std::random_device rd_;
	/** Singleton Mersenne Twister used */
	static std::mt19937_64 twister_;
	/** Private constructor.  No instantiating this class. */
	BaseRNG();
	// allow UniformRNG instances to all access a shared std::mt19937_64 instance
	template <class> friend class UniformRNG;
	template <class> friend class UniqueIntGenerator;
};



}/* End namespace rng */
#endif /* RANDOM_BASERNG_H_ */
