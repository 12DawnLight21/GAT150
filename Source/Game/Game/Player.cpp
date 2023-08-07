#include "Player.h"
#include "Health.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include "Framework/Resources/ResourceManager.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

#include "Game/SpaceRanch.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * umbra::g_time.GetDeltaTime();

	float thrust = 0;
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) thrust = 1;

	umbra::vec2 forward = umbra::vec2(0, -1).Rotate(m_transform.rotation);

	auto physicsComponent = GetComponent<umbra::PhysicsComponent>();
	physicsComponent->ApplyForce(forward * m_speed * thrust);
	physicsComponent->m_damping = 0.5f; //should slow me down

	m_transform.position.x = umbra::Wrap(m_transform.position.x, (float)umbra::g_renderer.GetWidth()); 
	m_transform.position.y = umbra::Wrap(m_transform.position.y, (float)umbra::g_renderer.GetHeight());

	// creating weapons
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon // projectiles
		umbra::Transform transform1{ m_transform.position, m_transform.rotation, 2}; //changes bullet size
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(400.0f, transform1);
		projectile->m_tag = "PlayerBullet";
		projectile->SetLifespan(1.0f);


		std::unique_ptr<umbra::SpriteComponent> component = std::make_unique<umbra::SpriteComponent>();
		component->m_texture = umbra::g_resources.Get<umbra::Texture>("playership.png", umbra::g_renderer);
		projectile->AddComponent(std::move(component));


		umbra::g_audioSystem.PlayOneShot("shoot");
		m_scene->Add(std::move(projectile));
	}

	// angled bullet
	/*
	umbra::Transform transform2{ m_transform.position, m_transform.rotation - umbra::DegToRad(10.0f), 2 };
	std::unique_ptr<Projectile> weapon = std::make_unique<Projectile>(400.0f, transform2, m_model);
	weapon->m_tag = "Player";
	weapon->SetLifespan(1.0f);
	m_scene->Add(std::move(weapon));
	*/
}

void Player::OnCollision(Actor* other)
{
	if (SpaceRanch::eState::Game)
	{
		if (other->m_tag == "Enemy" || other->m_tag == "EnemyBullet")
		{
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::PlayerDeadStart);
		}

		if (other->m_tag == "Power")
		{
			int value = Health::getValue(1, 5);

			m_game->SetLives(m_game->GetLives() + value);
			dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::Game);
		}
	}
}
