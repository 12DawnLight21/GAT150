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

        m_physicsComponent = GetComponent<PhysicsComponent>();

        auto collisionComponent = GetComponent<CollisionComponent>();
        if (collisionComponent)
        {
           

        }

        return true;
    }

    void Weapon::Update(float dt)
    {
        umbra::vec2 forward = umbra::vec2(0, -1).Rotate(transform.rotation);

        m_physicsComponent->SetVelocity(forward * speed);
        //transform.position += forward * speed * umbra::g_time.GetDeltaTime();

        transform.position.x = umbra::Wrap(transform.position.x, (float)umbra::g_renderer.GetWidth());
        transform.position.y = umbra::Wrap(transform.position.y, (float)umbra::g_renderer.GetHeight());
    }

    void Weapon::OnCollisionEnter(Actor* other)
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