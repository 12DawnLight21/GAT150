#pragma once
#include "Framework/Actor.h"

class Health : public umbra::Actor
{
	public:
		Health(const umbra::Transform transform, const std::shared_ptr<umbra::Model> model) :
			Actor{ transform, model }
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