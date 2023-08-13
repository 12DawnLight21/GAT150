#pragma once
#include "Framework/Actor.h"

class Projectile : public umbra::Actor
{
public:
	Projectile(float speed, const umbra::Transform transform) :
		Actor{ transform },
		m_speed{ speed } 
	{
		m_lifespan = 2.0f;
	};

	bool Initialize() override;

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
};
