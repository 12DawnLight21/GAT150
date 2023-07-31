#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace umbra
{
	class Actor
	{
	public:
		Actor(const Transform transform, const std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model } {};
		Actor(const Transform& transform) : m_transform{transform} {}

		virtual void Update(float dt); //dt = delta time
		virtual void Draw(Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; }
		virtual void OnCollision(Actor* other) {};

		void AddForce(const vec2& force) { m_velocity += force; };
		void SetDamping(float damping) { m_damping = damping; };

		float GetLifespan() { return m_lifespan; };
		float SetLifespan(float lifespan) { return m_lifespan = lifespan; };

		bool GetDestroyed() { return m_destroyed; };
		bool SetDestroyed(bool destroyed) { return m_destroyed = destroyed; };

		class Scene* m_scene = nullptr; //inline forward declaration
		friend class Scene;

		class Game* m_game = nullptr;

		Transform m_transform;
		std::string m_tag;

	protected:
		bool m_destroyed = false; //a flag
		float m_lifespan = -1.0f;

		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0; //if 0, no reduction, if 1, reduces fast
	};
}