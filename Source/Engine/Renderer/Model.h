#pragma once
#include "Core/Core.h"
#include "Framework/Resources/Resource.h"
#include <vector>

namespace umbra
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec3>& points) : m_points{ points } {};

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec3& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		//sphere collision
		float GetRadius();

		virtual bool Create(std::string filename, ...) override;
	private:
		std::vector<vec3> m_points; //hidden array of points ; vec2 = Vector2 alias
		
		//color class
		Color m_color;
		float m_radius = 0;

		// Inherited via Resource
	};
}