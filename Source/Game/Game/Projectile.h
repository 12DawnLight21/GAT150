#pragma once
#include "Framework/Actor.h"

namespace umbra
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(Actor* other);
		//void Read(const json_t& value);

	private:
		float speed = 0;
	};
}