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
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const Transform& transform) : transform{transform} {}

		virtual bool Initialize();
		virtual void OnDestroy();

		virtual void Update(float dt); //dt = delta time
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {};

		float GetLifespan() { return lifespan; };
		float SetLifespan(float lifespan) { return lifespan = lifespan; };

		bool GetDestroyed() { return destroyed; };
		bool SetDestroyed(bool destroyed) { return destroyed = destroyed; };

		class Scene* m_scene = nullptr; //inline forward declaration
		friend class Scene;

		class Game* m_game = nullptr;

	public:
		Transform transform;
		std::string tag;

	protected:
		std::vector<std::unique_ptr<Component>> components;

		bool destroyed = false; //a flag
		float lifespan = -1.0f;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get()); 
			if (result) return result;
		}

		return nullptr;
	}
}