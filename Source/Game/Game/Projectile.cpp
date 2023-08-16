#include "Projectile.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

bool Projectile::Initialize()
{
    auto collisionComponent = GetComponent<umbra::CollisionComponent>();
    if (collisionComponent)
    {
        auto renderComponent = GetComponent<umbra::RenderComponent>();
        if (renderComponent)
        {
            float scale = m_transform.scale;
            collisionComponent->m_radius = renderComponent->GetRadius() * scale;
        }
    }

    return true;
}

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	umbra::vec2 forward = umbra::vec2(0, -1).Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * umbra::g_time.GetDeltaTime();

	m_transform.position.x = umbra::Wrap(m_transform.position.x, (float)umbra::g_renderer.GetWidth());
	m_transform.position.y = umbra::Wrap(m_transform.position.y, (float)umbra::g_renderer.GetHeight());
}

void Projectile::OnCollision(Actor* other)
{
	if (other->m_tag != this->m_tag)
	{
		m_destroyed = true;
	}
}