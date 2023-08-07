#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Projectile : public umbra::Actor
{
public:
	Projectile(float speed, const umbra::Transform transform) :
		Actor{ transform },
		m_speed{ speed } 
	{
		m_lifespan = 2.0f;
	};

	void Update(float dt) override;
	//void PlaySound(umbra::AudioSystem audio);

	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
};
