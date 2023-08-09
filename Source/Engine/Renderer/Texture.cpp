#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace umbra
{
    Texture::~Texture()
    {
        if (m_texture) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Create(std::string filename, ...)
    {
        va_list args;

        va_start(args, filename);

        Renderer& renderer = va_arg(args, Renderer); 

        va_end(args);

        return Load(filename, renderer);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            WARNING_LOG("Filename " << " is invalid. Check your spelling!");
            return false;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        SDL_FreeSurface(surface);
        if (!m_texture)
        {
            WARNING_LOG("m_texture is NULL.");
            return false;
        }
        return true;
    }

    vec3 Texture::GetSize()
    {
        //assert if null??? 
        //ASSERT_LOG(!m_texture, "m_texture is NULL.");

        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);
        return vec2{ point.x, point.y };
    }


}