#pragma once
#include <cstdlib>
#include <ctime>
#include <type_traits>

//seed the random number genderator
inline void seedRandom(unsigned int seed)
{
	std::srand(seed);
}

//Generate a random float in the range [0, 1]
inline float random01()
{
	return static_cast<float>(std::rand()) / RAND_MAX;
}

//Generate a random float in the range [min, max]
inline float random(float min, float max)
{
	if (min > max)
		std::swap(min, max);

	return min + (max - min) * random01();
}