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

bool Enemy::Initialize()
{
	auto collisionComponent = GetComponent<umbra::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<umbra::RenderComponent>();
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

	umbra::vec2 forward = umbra::vec2(0, -1).Rotate(transform.rotation);
	Player* player = m_scene->GetActor<Player>(); //T* is replaced by player 
	if (player)
	{
		umbra::vec2 direction = player->transform.position - transform.position;

		float turnAngle = umbra::vec2::SignedAngle(forward, direction.Normalized());

		transform.rotation += turnAngle * dt;

		if (std::fabs(turnAngle) < umbra::DegToRad(30))
		{
			// shoot shoot bang boom
		}
	}

	transform.position += forward * m_speed * umbra::g_time.GetDeltaTime();
	transform.position.x = umbra::Wrap(transform.position.x, (float)umbra::g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
	transform.position.y = umbra::Wrap(transform.position.y, (float)umbra::g_renderer.GetHeight());

	//timer <= 0 reset time

	//uhhhh fires SUPER fast but if i change the firetimer value itll fix itself??
	//if (m_fireTimer <= 0)
	//{
	//	m_fireTimer = m_fireRate;

	//	//create weapon
	//	umbra::Transform transformm{ transform.position, transform.rotation, 2}; //changes bullet size
	//	std::unique_ptr<Weapon> projectile = std::make_unique<Weapon>(400.0f, transform);
	//	projectile->tag = "EnemyBullet";

	//	umbra::g_audioSystem.PlayOneShot("e_shoot");
	//	m_scene->Add(std::move(projectile));
	//}
	//else
	//{
	//	m_fireTimer -= dt;
	//}

}

void Enemy::OnCollision(Actor* other)
{
	if (other->tag == "PlayerBullet"  || other->tag == "Player")
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

		umbra::Transform transformm{transform.position, 0, 1};
		auto emitter = std::make_unique<umbra::Emitter>(transform, data);
		//emitter->m_lifespan = 1.0f; rewrote this to be better?
		emitter->SetLifespan(0.1f);
		m_scene->Add(std::move(emitter));

		m_game->AddPoints(100);
		destroyed = true;
		umbra::g_audioSystem.PlayOneShot("dead");
		dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::Game);
	}
}
