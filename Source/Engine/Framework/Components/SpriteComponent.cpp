#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace umbra
{
	void SpriteComponent::Update(float dt)
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, umbra::RadToDeg(m_owner->m_transform.rotation));
	}
}