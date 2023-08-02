#include "Player.h"
#include "Health.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

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
	AddForce(forward * m_speed * thrust); //if thrusting, we schmoovin


	//m_transform.position += forward * m_speed * thrust * umbra::g_time.GetDeltaTime();

	m_transform.position.x = umbra::Wrap(m_transform.position.x, (float)umbra::g_renderer.GetWidth()); //if i dont cast these to a float he stutters and dies
	m_transform.position.y = umbra::Wrap(m_transform.position.y, (float)umbra::g_renderer.GetHeight());

	// creating weapons
	// ranged
	if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon // projectiles
		umbra::Transform transform1{ m_transform.position, m_transform.rotation, 2}; //changes bullet size
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(400.0f, transform1, m_model);
		projectile->m_tag = "PlayerBullet";
		projectile->SetLifespan(1.0f);

		umbra::g_audioSystem.PlayOneShot("shoot");
		m_scene->Add(std::move(projectile));
	}	

	// melee
	//if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_M) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_M))
	//{
	//	//create weapon //for now he's a melee boi
	//	umbra::Transform transform2{ m_transform.position, m_transform.rotation, 1}; //changes bullet size
	//	std::unique_ptr<Projectile> melee = std::make_unique<Projectile>( 0, transform2, m_model );
	//	melee->m_tag = "Player";
	//	melee->SetLifespan(0.01f);

	//	umbra::g_audioSystem.PlayOneShot("shoot");
	//	m_scene->Add(std::move(melee))
	//}


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
