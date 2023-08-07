#pragma once
#include "Framework/Actor.h"

class Health : public umbra::Actor
{
	public:
		Health(const umbra::Transform transform) :
			Actor{ transform }
		{};

		static int getValue(int min, int max)
		{
			int value = umbra::random(min, max);
			return value;
		}

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

		friend class Player;

	private:
		int m_minValue = 1;
		int m_maxValue = 5;
};