#pragma once
#include <cmath>

namespace umbra
{
	constexpr float Pi = 3.14159265359f; //a constant expression that can be evaluated at run/compile time
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); };
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); };

	constexpr int Wrap(int value, int max) //makes the ship stutter with some angles
	{
		return (value % max) + ((value < 0) ? max : 0);
	};

	inline float Wrap(float value, float max) //can account for the float values of the angles, makin it schmoove
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	//templates define a function/classes and substitutes data types later
	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b; //if a > b, return a, else return b
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max) //4-10 -> 3
	{
		if (min > max) std::swap(min, max); //swaps values, might not work

		if (value < min) value = min;
		else if (value > max) value = max;

		return value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) // t = 0 <-> 1
	{
		return (a * (1.0f - t)) + (b * t);
	}

}