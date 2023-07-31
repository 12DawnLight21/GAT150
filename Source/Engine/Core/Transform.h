#pragma once
#include "Core.h"

namespace umbra
{
	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1.0f;

	public:
		Transform() = default;

		Transform(const vec2 position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {};
	};
}