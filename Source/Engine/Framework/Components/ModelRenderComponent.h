#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace umbra
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent);

		bool Initialize() override;
		void Update(float dt);
		void Draw(class Renderer& renderer);

		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		ModelRenderComponent() = default;

		std::string modelName;
		res_t<Model> m_model;
	};
}