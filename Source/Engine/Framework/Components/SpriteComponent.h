#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace umbra
{
	class SpriteComponent : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(class Renderer& renderer);

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }
	public:
		res_t<Texture> m_texture;
	};
}