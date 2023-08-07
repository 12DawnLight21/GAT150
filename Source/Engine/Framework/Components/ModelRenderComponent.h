#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace umbra
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(class Renderer& renderer);

	public:
		//res_t<Model> m_texture;
	};
}