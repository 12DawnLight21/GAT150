#pragma once
#include "Framework/Framework.h"
#include "Framework/Components/PhysicsComponent.h"

namespace umbra
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy() = default;

		bool Initialize() override;

		void OnDestroy() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}