#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace umbra
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec3& force) = 0;

	public:
		vec3 m_velocity;
		vec3 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}