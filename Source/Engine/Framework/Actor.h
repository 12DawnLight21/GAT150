#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace umbra
{
	class Actor : public Object
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{transform} {}

		virtual bool Initialize();
		virtual void OnDestroy();

		virtual void Update(float dt); //dt = delta time
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {};

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
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false; //a flag
		float m_lifespan = -1.0f;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get()); 
			if (result) return result;
		}

		return nullptr;
	}
}