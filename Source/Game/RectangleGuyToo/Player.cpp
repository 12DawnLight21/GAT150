#include "Player.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"

namespace umbra
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//move ment
		float dir = 0; //direction!
		if (g_inputSystem.getKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_inputSystem.getKeyDown(SDL_SCANCODE_D)) dir = 1;

		vec2 forward = vec2{ 1, 0 };

		m_physicsComponent->ApplyForce(forward * speed * dir);

		transform.position.x = Wrap(transform.position.x, (float)g_renderer.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_renderer.GetHeight());

		//jump jump
		bool onGround = (groundCount > 0);

		if (onGround && g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			vec2 up = vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		//animation please just work and not cause problems PLEASE JUST WORK AND DONT CAUSE PROBLEMS
		vec2 velocity = m_physicsComponent->velocity;

		if (std::fabs(velocity.x > 0.2f))
		{
			//am i movin?
			m_spriteAnimComponent->flipH = (dir < 0); //if backwards FLIPPIE
			m_spriteAnimComponent->SetSequence("run");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
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