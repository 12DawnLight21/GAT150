#include "Actor.h"
#include "Framework/Components/Component.h"
#include "Framework/Components/RenderComponent.h"

namespace umbra
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(umbra::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_transform);
		for (auto& component : m_components)
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
		m_components.push_back(std::move(component));
	}
}