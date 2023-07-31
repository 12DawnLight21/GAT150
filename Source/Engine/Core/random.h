#pragma once
#include <iostream>

//maple calls this kiko in his stuff!
namespace umbra
{
	//inlines replaces the function name with the functions code
	inline void seedRandom(unsigned int seed) { srand(seed); } //unsigned = no negative
	inline int random() { return rand(); }
	inline int random(unsigned int max) { return rand() % max; } //return 0 - (max - 1)
	inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } //returns between min & max (inclusive)

	inline float randomf() { return random() / (float)RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { return min + randomf(max - min); }
}