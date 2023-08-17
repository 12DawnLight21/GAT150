#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace umbra
{
	CLASS_DEFINITION(EnginePhysicsComponent)

	void EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt; //pointer to incomplete class = include the class dummy
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}
}