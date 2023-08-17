#pragma once
#include "Framework/Actor.h"

class Enemy : public umbra::Actor
{
public:
	Enemy(float speed, float turnRate, const umbra::Transform transformm) :
		Actor{ transformm },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 3.0f;
		m_fireTimer = m_fireRate;
	};

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* oother) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0; 
	float m_fireTimer = 0; //how often it shoots

	float m_health = 10;
	//float m_damage = 10;
};