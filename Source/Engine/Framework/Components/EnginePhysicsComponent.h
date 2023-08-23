#pragma once
#include "PhysicsComponent.h"

//our basic ass physics component

namespace umbra
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)

		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;

		void ApplyTorque(float torque) override;
	};
}