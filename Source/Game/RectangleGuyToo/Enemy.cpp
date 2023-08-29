#include "Enemy.h"
#include "Player.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"

namespace umbra
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<umbra::PhysicsComponent>();

		return true;
	}

	void Enemy::OnDestroy()
	{
		Actor::OnDestroy();
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		//move ment
		float dir = 0;
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) dir = 1;

		m_physicsComponent->ApplyForce(forward * speed * dir);
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
		}

		if (other->tag == "Ground") groundCount++;
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--; //we leavin the ground fellas
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}