#include "Projectile.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

namespace umbra
{
    bool WeaponComponent::Initialize() 
    {
        auto collisionComponent = m_owner->GetComponent<umbra::CollisionComponent>(); //get the actor that owns us since we're just a component now
        if (collisionComponent)
        {
            auto renderComponent = m_owner->GetComponent<umbra::RenderComponent>();
            if (renderComponent)
            {
                float scale = m_owner->transform.scale;
                collisionComponent->m_radius = renderComponent->GetRadius() * scale;
            }
        }

        return true;
    }

    void WeaponComponent::Update(float dt)
    {
        umbra::vec2 forward = umbra::vec2(0, -1).Rotate(m_owner->transform.rotation);
        m_owner->transform.position += forward * speed * umbra::g_time.GetDeltaTime();

        m_owner->transform.position.x = umbra::Wrap(m_owner->transform.position.x, (float)umbra::g_renderer.GetWidth());
        m_owner->transform.position.y = umbra::Wrap(m_owner->transform.position.y, (float)umbra::g_renderer.GetHeight());
    }

    void WeaponComponent::OnCollision(Actor* other)
    {
        if (other->tag != m_owner->tag)
        {
            m_owner->SetDestroyed(true);
        }
    }
    void WeaponComponent::Read(const json_t& value)
    {
        //
    }
}