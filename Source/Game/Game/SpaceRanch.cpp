#include "SpaceRanch.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"


bool SpaceRanch::Initialize()
{
	//create font / text
	m_font = GET_RESOURCE(umbra::Font, "MinecraftRegular.ttf", 24);

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

	//create scene
	m_scene = std::make_unique<umbra::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

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
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName<umbra::Actor>("Background")->active = false;
		}
		break;

	case SpaceRanch::StartGame:
		m_score = 0;
		m_lives = 50;
		if (m_stateTimer != 3) m_stateTimer = 3;

		m_state = eState::StartLevel;
		break;

	case SpaceRanch::StartLevel:
		m_scene->RemoveAll(true); //check this to see if its right later
		{
			//Create Player
			m_scene->RemoveAll(true);
			auto player = std::make_unique<Player>(10.0f, umbra::Pi, umbra::Transform{ {400, 300}, 0, 1 });
			player->tag = "Player";
			player->m_game = this;

			//create Components
			auto renderComponent = CREATE_NAMESPACE_CLASS(SpriteComponent); //umbra::Factory::Instance().Create<umbra::SpriteComponent>("SpriteComponent"); //original >>>> std::make_unique<umbra::SpriteComponent>();
			renderComponent->m_texture = GET_RESOURCE(umbra::Texture, "playership.png", umbra::g_renderer);
			//renderComponent->m_texture = umbra::g_resources.Get<umbra::Texture>("playership.png", umbra::g_renderer);
			player->AddComponent(std::move(renderComponent));

			//adding physics
			auto physicsComponent = std::make_unique<umbra::EnginePhysicsComponent>();
			physicsComponent->m_damping = 0.5f;
			player->AddComponent(std::move(physicsComponent));

			auto collisionComponent = std::make_unique<umbra::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			player->Initialize();
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

			//added this before i was supposed too i think
			auto enemy = std::make_unique<Enemy>(umbra::randomf(75.0f, 150.0f), umbra::Pi, umbra::Transform{{400, 300}, 0, 1});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto renderComponent = umbra::Factory::Instance().Create<umbra::SpriteComponent>("SpriteComponent");
			renderComponent->m_texture = GET_RESOURCE(umbra::Texture, "playership.png", umbra::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			//adding physics
			auto physicsComponent = std::make_unique<umbra::EnginePhysicsComponent>(); 
			physicsComponent->m_damping = 0.5f; 
			enemy->AddComponent(std::move(physicsComponent)); 

			auto collisionComponent = std::make_unique<umbra::CircleCollisionComponent>(); 
			collisionComponent->m_radius = 30.0f; 
			enemy->AddComponent(std::move(collisionComponent)); 

			enemy->Initialize(); 
			m_scene->Add(std::move(enemy)); 
		}

		if (m_powerTimer >= m_powerTime)
		{
			m_powerTimer = 0;
			std::unique_ptr<Health> power = std::make_unique<Health>(umbra::Transform{ { umbra::random(800), umbra::random(600)}, umbra::randomf(umbra::TwoPi), 6 });
			power->tag = "Power";
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

		m_scene->RemoveAll(true);

		//umbra::EmitterData data;
		//data.burst = true;
		//data.burstCount = 100;
		//data.spawnRate = 200;
		//data.angle = 0;
		//data.angleRange = umbra::Pi;
		//data.lifetimeMin = 0.5f;
		//data.lifetimeMin = 1.5f;
		//data.speedMin = 50;
		//data.speedMax = 250;
		//data.damping = 0.5f;
		//data.color = umbra::Color{ 1, 0, 0, 1 };

		//umbra::Transform death{umbra::random(umbra::g_renderer.GetWidth()), umbra::random(umbra::g_renderer.GetHeight()), 1};
		//auto emitter = std::make_unique<umbra::Emitter>(death, data);
		////emitter->m_lifespan = 1.0f; rewrote this to be better?
		//emitter->SetLifespan(0.1f);
		//m_scene->Add(std::move(emitter));

		if (m_stateTimer <= 0)
			{
				m_scene->RemoveAll(true);
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
	m_scene->Draw(renderer);

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
	umbra::g_particleSystem.Draw(renderer);
}
