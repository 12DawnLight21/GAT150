#include "Projectile.h"
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Framework/Components/CollisionComponent.h"

namespace umbra
{
    CLASS_DEFINITION(Weapon)

    bool Weapon::Initialize() 
    {
        Actor::Initialize();

        auto collisionComponent = GetComponent<CollisionComponent>(); //get the actor that owns us since we're just a component now
        if (collisionComponent)
        {
            auto renderComponent = GetComponent<RenderComponent>();
            if (renderComponent)
            {
                float scale = transform.scale;
                collisionComponent->m_radius = renderComponent->GetRadius() * scale;
            }
        }

        return true;
    }

    void Weapon::Update(float dt)
    {
        umbra::vec2 forward = umbra::vec2(0, -1).Rotate(transform.rotation);
        transform.position += forward * speed * umbra::g_time.GetDeltaTime();

        transform.position.x = umbra::Wrap(transform.position.x, (float)umbra::g_renderer.GetWidth());
        transform.position.y = umbra::Wrap(transform.position.y, (float)umbra::g_renderer.GetHeight());
    }

    void Weapon::OnCollision(Actor* other)
    {
        if (other->tag != tag)
        {
            SetDestroyed(true);
        }
    }

    void Weapon::Read(const json_t& value)
    {
        Actor::Read(value);
        READ_DATA(value, speed);
    }
}