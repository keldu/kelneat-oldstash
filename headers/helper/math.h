#pragma once

#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace KelNeat{
	const uint32_t random_steps = 10000;

	inline void seed(){
		uint32_t seed = time(0L);
		srand(seed);
	}

	inline double random(double min, double max, uint32_t steps){
		double diff = max - min;
		double randomNumber = (rand() % steps) / (double)(steps-1.0);
		return randomNumber * diff + min;
	}

	inline size_t random(size_t max){
		size_t r = rand();
		return r % max;
	}

	inline double sigmoid(double t){
		return t / sqrt(1.0 + t * t);
	}
}