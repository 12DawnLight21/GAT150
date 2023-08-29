#include "Actor.h"
#include "Components/RenderComponent.h"

namespace umbra
{
	CLASS_DEFINITION(Actor)

		Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;
		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0.0f);
		}
		for (auto& component : components) //fix a issue with unique ptr and make it & actor
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(umbra::Renderer& renderer)
	{
		for (auto& component : components) //fix a issue with unique ptr and make it & actor
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);
				auto component = umbra::Factory::Instance().Create<umbra::Component>(type);
				component->Read(componentValue); //spriteanimrendercomponent component._Mypair._Myval2 was nullptr

				AddComponent(std::move(component));
			}
		}
	}
}