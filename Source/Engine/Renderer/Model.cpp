#include "Model.h"
#include "Renderer.h"
#include <sstream>

namespace umbra
{
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		umbra::readFile(filename, buffer);

		std::istringstream stream(buffer); 

		//reads color
		stream >> m_color;

		//reads number of points
		std::string line;
		std::getline(stream, line);
		int numPoints = std::stoi(line);

		//reads vec2 points
		for (int i = 0; i < numPoints; i++)
		{
			vec2 point;

			stream >> point;

			m_points.push_back(point); //assigns point to vec even tho there's no data
		}

		return true;
	}

	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) return; //if there's no points, don't draw

		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

		for (int i = 0; i < m_points.size() - 1; i++) //prevents me from going outside the index
		{

			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position; //we scale along the origin, then rotate, then place
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;
			
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		if (m_points.empty()) return;

		mat3 mx = transform.GetMatrix(); //const correctness at it again!


		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			vec2 p1 = mx * m_points[i];
			vec2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	float Model::GetRadius()
	{
		if (m_radius) return m_radius;

		for (auto point : m_points)
		{
			float length = point.Length();
			m_radius = Max(m_radius, length); //radius = highest value from points
		}

		return m_radius;
	}

	bool Model::Create(std::string filename, ...)
	{
		return Load(filename);
	}
}