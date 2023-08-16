#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace umbra
{
	CLASS_DEFINITION(ModelRenderComponent);

	void ModelRenderComponent::Update(float dt)
	{

	}
	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}
}