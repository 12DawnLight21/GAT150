#pragma once
#include "Core/Core.h"
#include "Renderer.h" 
#include <vector>

namespace umbra
{
	class Model //draws points with lines and lines with points
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}; //if you dont use a reference, itll copy over the numbers which is SLOW

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		//sphere collision
		float GetRadius();

	private:
		std::vector<vec2> m_points; //hidden array of points ; vec2 = Vector2 alias
		
		//color class
		Color m_color;
		float m_radius = 0;
	};
}