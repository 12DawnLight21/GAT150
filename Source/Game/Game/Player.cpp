#include "Player.h"
#include "Health.h"
#include "Projectile.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"

bool Player::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<umbra::PhysicsComponent>();

	///new
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

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) rotate = 1;
	//transform.rotation += rotate * m_turnRate * umbra::g_time.GetDeltaTime();
	m_physicsComponent->ApplyTorque(rotate * m_turnRate); //box2d already grabs deltatime

	float thrust = 0;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) thrust = 1;
	umbra::vec2 forward = umbra::vec2{ 0, -1 }.Rotate(transform.rotation);

	///VVVVVS
	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	transform.position.x = umbra::Wrap(transform.position.x, (float)umbra::g_renderer.GetWidth());
	transform.position.y = umbra::Wrap(transform.position.y, (float)umbra::g_renderer.GetHeight());

	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		auto weapon = INSTANTIATE(umbra::Weapon, "Rocket");
		weapon->transform = { transform.position, transform.rotation, 1.0f };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}
}

void Player::OnCollision(Actor* other)
{
	if (SpaceRanch::eState::Game)
	{
		if (other->tag == "Enemy" || other->tag == "EnemyBullet")
		{
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::PlayerDeadStart);
		}

		if (other->tag == "Power")
		{
			int value = Health::getValue(1, 5);

			m_game->SetLives(m_game->GetLives() + value);
			dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::Game);
		}
	}
}
