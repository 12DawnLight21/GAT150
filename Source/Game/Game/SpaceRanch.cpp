#include "SpaceRanch.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"

bool SpaceRanch::Initialize()
{
	//create font / text
	m_font = std::make_shared<umbra::Font>("MinecraftRegular.ttf", 24);
	m_scoreText = std::make_unique<umbra::Text>(m_font);
	m_scoreText->Create(umbra::g_renderer, "SCORE", umbra::Color{1, 0, 1, 1});

	m_lifeText = std::make_unique<umbra::Text>(m_font);
	m_lifeText->Create(umbra::g_renderer, "LIVES", umbra::Color{1, 0, 1, 1});

	m_tutorialText = std::make_unique<umbra::Text>(m_font);
	m_tutorialText2 = std::make_unique<umbra::Text>(m_font);
	m_tutorialText->Create(umbra::g_renderer, "W to thrust, A and D to turn!", umbra::Color{1, 1, 1, 1});
	m_tutorialText2->Create(umbra::g_renderer, "Space is to shoot but ramming into enemies works in a pinch.", umbra::Color{1, 1, 1, 1});

	m_titleText = std::make_unique<umbra::Text>(m_font);
	m_titleText->Create(umbra::g_renderer, "S P A C E   R A N C H", umbra::Color{1, 1, 1, 1});
	
	m_gameOverText = std::make_unique<umbra::Text>(m_font);
	m_gameOverText->Create(umbra::g_renderer, "GAME OVER", umbra::Color{1, 0, 0, 1});

	//load audio
	umbra::g_audioSystem.AddAudio("shoot", "shoot.wav"); 
	umbra::g_audioSystem.AddAudio("e_shoot", "enemy_shoot.wav"); 
	umbra::g_audioSystem.AddAudio("bg_music", "TheHandoftheQueen.wav"); 
	umbra::g_audioSystem.AddAudio("dead", "Explosion.wav"); 

	m_scene = std::make_unique<umbra::Scene>();

	return true;
}

bool SpaceRanch::Shutdown()
{
	//nothing yet
	return false;
}

void SpaceRanch::Update(float dt)
{
	switch (m_state)
	{
	case SpaceRanch::Title:
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_RETURN))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceRanch::StartGame:
		m_score = 0;
		m_lives = 50;
		if (m_stateTimer != 3) m_stateTimer = 3;

		m_state = eState::StartLevel;
		break;

	case SpaceRanch::StartLevel:
		m_scene->RemoveAll();
		{
			std::unique_ptr<Player> player = std::make_unique<Player>(12.0f, umbra::Pi, umbra::Transform{ {400, 300}, 0, 6 }, umbra::g_manager.Get("player.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			player->SetDamping(0.8f);
			m_scene->Add(std::move(player));
		}
			m_state = eState::Tutorial;
		break;

	case SpaceRanch::Tutorial:
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_RETURN) && !umbra::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_RETURN))
		{
			m_state = eState::Game;
		}
		break;

	case SpaceRanch::Game:
		if (this->m_lives <= 0)
		{
			m_state = eState::GameOverStart;
		}

		m_spawnTimer += dt;
		m_powerTimer += dt;

		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(umbra::randomf(75.0f, 150.0f), umbra::Pi, umbra::Transform{ { umbra::random(800), umbra::random(600)}, umbra::randomf(umbra::TwoPi), 6 }, umbra::g_manager.Get("enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}

		if (m_powerTimer >= m_powerTime)
		{
			m_powerTimer = 0;
			std::unique_ptr<Health> power = std::make_unique<Health>(umbra::Transform{ { umbra::random(800), umbra::random(600)}, umbra::randomf(umbra::TwoPi), 6 }, umbra::g_manager.Get("health.txt"));
			power->m_tag = "Power";
			power->m_game = this;
			m_scene->Add(std::move(power));
		}

		//clicks make particles but do nothing else
		if (umbra::g_inputSystem.GetMouseButtonDown(0)) //if mouse clicked, clicked the mouse
		{
			umbra::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = umbra::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = umbra::Color{ 143.8f, 5.2f, 6.4f, 1 };

			umbra::Transform transform{ { umbra::g_inputSystem.GetMousePosition() }, 0, 1 };
			auto emitter = std::make_unique<umbra::Emitter>(transform, data);
			//emitter->m_lifespan = 1.0f; rewrote this to be better?
			emitter->SetLifespan(emitter->GetLifespan());
			m_scene->Add(std::move(emitter));
		}

		break;
	case SpaceRanch::PlayerDeadStart:
		if (m_lives < m_lives)
		{
			umbra::g_audioSystem.PlayOneShot("dead");
		}
		else m_state = eState::PlayerDead;
		break;

	case SpaceRanch::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::Game;
		}
		break;

	case SpaceRanch::GameOverStart:
		m_stateTimer *= 2;
		m_state = eState::GameOver;
		break;

	case SpaceRanch::GameOver:
	{
		m_stateTimer -= dt;

		m_scene->RemoveAll();

		umbra::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = umbra::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = umbra::Color{ 1, 0, 0, 1 };

		umbra::Transform death{umbra::randomf(umbra::g_renderer.GetWidth()), umbra::randomf(umbra::g_renderer.GetHeight()), 1};
		auto emitter = std::make_unique<umbra::Emitter>(death, data);
		//emitter->m_lifespan = 1.0f; rewrote this to be better?
		emitter->SetLifespan(0.1f);
		m_scene->Add(std::move(emitter));

		if (m_stateTimer <= 0)
			{
				m_scene->RemoveAll();
				m_state = eState::Title;
			}
		}
		break;

	default:
		break;
	}

	m_scoreText->Create(umbra::g_renderer, std::to_string(m_score), {1, 0, 1, 1});
	m_lifeText->Create(umbra::g_renderer, std::to_string(m_lives), {1, 0, 1, 1});
	m_scene->Update(dt);
}

void SpaceRanch::Draw(umbra::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 275, 275);
	}

	if (m_state == eState::Tutorial)
	{
		m_tutorialText->Draw(renderer, 225, 275);
		m_tutorialText2->Draw(renderer, 50, 325);
	}
	
	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 40);
	m_lifeText->Draw(renderer, 40, 80);
	m_scene->Draw(renderer);
	umbra::g_particleSystem.Draw(renderer);
}
