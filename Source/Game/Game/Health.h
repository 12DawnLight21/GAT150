#pragma once
#include "Framework/Actor.h"

class Health : public umbra::Actor
{
	public:
		Health(const umbra::Transform transform, const std::shared_ptr<umbra::Model> model) :
			Actor{ transform, model }
		{};

		static float getValue(float min, float max)
		{
			float value = umbra::randomf(min, max);
			return value;
		}

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

		friend class Player;

	private:
		float m_minValue = 1;
		float m_maxValue = 5;
};