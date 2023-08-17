#include "Actor.h"
#include "Framework/Components/Component.h"
#include "Framework/Components/RenderComponent.h"

namespace umbra
{
	CLASS_DEFINITION(Actor)

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
		if (lifespan != -1)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(umbra::Renderer& renderer)
	{
		for (auto& component : components)
		{
			RenderComponent* r_component = dynamic_cast<RenderComponent*>(component.get());
			if (r_component)
			{
				r_component->Draw(renderer);
			}
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component)); //this gives me error ;/
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);

		if (HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_NAMESPACE_CLASSBASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component)); //have to move it cause its a unique pointer
			}
		}
	}
}