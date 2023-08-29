#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"


namespace umbra
{
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize()
	{
		m_physicsComponent = GetComponent<PhysicsComponent>(); //delete the umbra once we're in the namespace

		auto collisionComponent = GetComponent<CollisionComponent>();
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

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		vec2 forward = umbra::vec2(0, -1).Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>(); //T* is replaced by player 
		if (player)
		{
			vec2 direction = player->transform.position - transform.position;

			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());

			//transform.rotation += turnAngle * dt;
			m_physicsComponent->ApplyTorque(turnAngle);

			if (std::fabs(turnAngle) < DegToRad(30))
			{
				// shoot shoot bang boom
			}
		}

		m_physicsComponent->ApplyForce(forward * speed);

		//transform.position += forward * m_speed * umbra::g_time.GetDeltaTime();
		transform.position.x = Wrap(transform.position.x, (float)g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
		transform.position.y = Wrap(transform.position.y, (float)g_renderer.GetHeight());
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "PlayerBullet" || other->tag == "Player")
		{
			//create explosion
			umbra::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = umbra::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = umbra::Color{ 1, 0, 0, 1 };

			Transform transformm{ transform.position, 0, 1 };
			auto emitter = std::make_unique<Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));

			m_game->AddPoints(100);
			destroyed = true;
			umbra::g_audioSystem.PlayOneShot("dead");
			dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::Game);
		}
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, fireRate);
	}

}