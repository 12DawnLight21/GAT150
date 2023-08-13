#pragma once
#include "Framework/Framework.h"

class Player : public umbra::Actor
{
public:
	Player(float speed, float turnRate, const umbra::Transform transform) :
		Actor{ transform },
		m_speed{speed},
		m_turnRate{turnRate}
	{};

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	umbra::PhysicsComponent* m_physicsComponent = nullptr;
};