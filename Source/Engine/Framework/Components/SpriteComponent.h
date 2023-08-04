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

	public:
		res_t<Texture> m_texture;
	};
}