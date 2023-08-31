#include "RectangleGug.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Events/EventManager.h"


bool RectangleGug::Initialize()
{
	//load audio
	umbra::g_audioSystem.AddAudio("bg_music", "audio/MayorMOnee.wav");
	umbra::g_audioSystem.AddAudio("chomp", "audio/Chomp.wav");

	//create scene
	m_scene = std::make_unique<umbra::Scene>();
	m_scene->Load("scenes/scene.json");
	m_scene->Load("scenes/tilemap.json");

	m_scene->Load("scenes/title.json");
	m_scene->Initialize();

	//EVENT_SUBSCRIBE("OnAddPoints", RectangleGug::OnAddPoints);
	//EVENT_SUBSCRIBE("OnPlayerDead", RectangleGug::OnPlayerDead);

	return true;
}

bool RectangleGug::Shutdown()
{
	//nothing yet
	return false;
}

void RectangleGug::Update(float dt)
{
	switch (m_state)
	{
	case RectangleGug::Title:
		m_scene->GetActorByName<umbra::Actor>("Score")->active = false;
		m_scene->GetActorByName<umbra::Actor>("Win")->active = false;

		m_scene->GetActorByName<umbra::Enemy>("Bat")->active = false;
		m_scene->GetActorByName<umbra::Enemy>("Tard")->active = false;

		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName<umbra::Actor>("Title")->active = false;
			m_scene->GetActorByName<umbra::Actor>("Instructions")->active = false;
		}
		break;

	case RectangleGug::StartGame:
		m_score = 0;
		m_lives = 3;

		m_scene->GetActorByName<umbra::Actor>("Score")->active = true;

		m_state = eState::StartLevel;
		break;

	case RectangleGug::StartLevel:
		m_state = eState::Game;
		
		break;

	case RectangleGug::Game:
	{
		m_scene->GetActorByName<umbra::Enemy>("Bat")->active = true;
		m_scene->GetActorByName<umbra::Enemy>("Tard")->active = true;

			if (m_scene->GetActorByName<umbra::Enemy>("Bat")->destroyed)
			{
				m_score++;
				m_scene->GetActorByName<umbra::Enemy>("Bat")->destroyed = false;

				std::cout << "SCORE: " << m_score << "\n";
			}

			if (m_scene->GetActorByName<umbra::Enemy>("Tard")->destroyed)
			{
				m_score++;
				m_scene->GetActorByName<umbra::Enemy>("Tard")->destroyed = false;

				std::cout << "SCORE: " << m_score << "\n";
			}

			if (m_score >= 25)
			{
				m_state = eState::GameOver;
			}
	}
		break;

	case RectangleGug::GameOver:
		
		m_scene->GetActorByName<umbra::Actor>("Score")->active = true;
		m_scene->GetActorByName<umbra::Actor>("Win")->active = true;
		
		break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void RectangleGug::Draw(umbra::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void RectangleGug::OnAddPoints(const umbra::Event& event)
{
	m_score += std::get<int>(event.data);
}

void RectangleGug::OnPlayerDead(const umbra::Event& event)
{
	m_lives--;
	m_state = eState::StartLevel;
}