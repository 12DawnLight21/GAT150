#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace umbra
{
	class Enemy : public Actor
	{

	public:
		CLASS_DECLARATION(Enemy)
		Enemy() = default;

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* oother) override;


	private:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0; //how often it shoots

		float m_health = 10;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}