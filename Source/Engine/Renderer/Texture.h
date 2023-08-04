#pragma once
#include "Core/Vector2.h"
#include "Framework/Resources/Resource.h"

struct SDL_Texture;

namespace umbra
{
	class Texture : Resource
	{
	public:
		Texture() = default;
		~Texture();

		virtual bool Create(std::string filename, ...) override;

		bool Load(const std::string& filename, class Renderer& renderer);
		vec2 GetSize();

		SDL_Texture* GetTexture() { return m_texture; }

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}