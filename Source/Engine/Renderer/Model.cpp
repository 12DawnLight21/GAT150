#include "Model.h"
#include <sstream>

namespace umbra
{
	bool Model::Load(const std::string& filename)
	{
		std::string buffer; //fancy name for block of data
		umbra::readFile(filename, buffer);

		//std::cout << buffer << std::endl;

		std::istringstream stream(buffer); //turns the buffer into a string

		//reads color
		stream >> m_color;

		//reads number of points
		std::string line;
		std::getline(stream, line);
		int numPoints = std::stoi(line); //converts string to int

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
		Draw(renderer, transform.position, transform.rotation, transform.scale);
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
}