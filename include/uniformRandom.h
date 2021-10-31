/*=========================================================================

Project:   Illuvatar
File:      uniformRandom.h

Copyright (c) 2021 - All rights reserved
Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#ifndef ILLUVATAR_UNIFORMRANDOM_H
#define ILLUVATAR_UNIFORMRANDOM_H

#include <random>
#include <iterator>

template <typename RandomGenerator = std::default_random_engine> struct uniformRandom {
	//On most platforms, you probably want to use std::random_device("/dev/urandom")()
	uniformRandom(RandomGenerator g = RandomGenerator(std::random_device()())) : gen(g) {}

	template <typename Iter> Iter select(Iter start, Iter end) {
		std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}

	//convenience function
	template <typename Iter> Iter operator()(Iter start, Iter end) {
		return select(start, end);
	}

	//convenience function that works on anything with a sensible begin() and end(), and returns with a ref to the value type
	template <typename Container>
	auto operator()(const Container& c) -> decltype(*begin(c))& {
		return *select(begin(c), end(c));
	}

  	private:
		RandomGenerator gen;
};

#endif // ILLUVATAR_UNIFORMRANDOM_H
