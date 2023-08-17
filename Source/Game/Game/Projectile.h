#pragma once
#include "Framework/Components/Component.h"

namespace umbra
{
	class WeaponComponent : public Component //renamed weapon to weaponComponent
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