#pragma once
#include "Framework/Actor.h"

namespace umbra
{
	class Weapon : public Actor
	{
	public:
		/*Projectile(float speed, const umbra::Transform transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		};
		*/

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(Actor* other);
		void Read(const json_t& value);

	private:
		float speed = 0;
	};
}