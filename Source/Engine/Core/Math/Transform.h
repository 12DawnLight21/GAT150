#pragma once
#include "Core/Core.h" //includes my json file anyways
#include "Matrix22.h"
#include "Matric33.h"

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

		mat3 GetMatrix() const
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			mat3 mx = mt * ms * mr;

			return mx;
		}

		void Read(const json_t& value);
	};
}