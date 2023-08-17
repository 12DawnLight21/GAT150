#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resources/ResourceManager.h"

namespace umbra
{
	CLASS_DEFINITION(SpriteComponent)

		bool SpriteComponent::Initialize()
	{
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{
		//
	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value)
	{
		READ_DATA(value, textureName);

		
	}
}