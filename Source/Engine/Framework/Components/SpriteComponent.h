#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace umbra
{
	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		bool Initialize() override;
		void Update(float dt);
		void Draw(class Renderer& renderer);

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }

	public:
		Rect source;
		bool flipH = false;
		vec2 origin{0.5f, 0.5f};

		std::string textureName;
		res_t<Texture> m_texture;
	};
}