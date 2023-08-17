#pragma once
#include "Actor.h"

#include <list>
//unity calls these scenes too

namespace umbra
{
	//forward declaration - tells the compiler that it doesnt need to know shit bout the renderer's reference
		//doesnt work with functions, can only declare variables
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors; //contains POINTER of actors, more optimal for constantly changing
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors) //if unique_ptr, MUST be reference!
		{
			T* result = dynamic_cast<T*>(actor.get()); //goes through every actor and returns the one we specify
			if (result) return result;
		}

		return nullptr;
	}
}