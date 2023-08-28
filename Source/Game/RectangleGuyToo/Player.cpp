#include "Player.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"

namespace umbra
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<umbra::PhysicsComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//move ment
		float dir = 0; //direction!
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) dir = 1;

		umbra::vec2 forward = umbra::vec2{ 1, 0 };

		m_physicsComponent->ApplyForce(forward * speed * dir);

		transform.position.x = umbra::Wrap(transform.position.x, (float)umbra::g_renderer.GetWidth());
		transform.position.y = umbra::Wrap(transform.position.y, (float)umbra::g_renderer.GetHeight());

		//jump jump
		bool onGround = (groundCount > 0);
		if (onGround && umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			umbra::vec2 up = umbra::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
		}

		if (other->tag == "Ground") groundCount++;
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--; //we leavin the ground fellas
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}