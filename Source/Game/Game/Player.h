#pragma once
#include "Framework/Actor.h"

class Player : public umbra::Actor
{
public:
	Player(float speed, float turnRate, const umbra::Transform transform, const std::shared_ptr<umbra::Model> model) :
		Actor{ transform, model },
		m_speed{speed},
		m_turnRate{turnRate}
	{};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};