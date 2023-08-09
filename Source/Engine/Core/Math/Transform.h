#pragma once
#include "Core.h"
#include "Matrix22.h"

namespace umbra
{
	class Transform
	{
	public:
		vec3 position;
		float rotation = 0;
		float scale = 1.0f;

	public:
		Transform() = default;

		Transform(const vec3 position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {};

		mat2 GetMatrix() const
		{
			mat2 ms = mat2::CreateScale(scale);
			mat2 mr = mat2::CreateRotation(rotation);

			return ms * mr;
		}
	};
}