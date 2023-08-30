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
	//umbra::g_audioSystem.AddAudio("shoot", "shoot.wav");
	//umbra::g_audioSystem.AddAudio("e_shoot", "enemy_shoot.wav");
	//umbra::g_audioSystem.AddAudio("bg_music", "TheHandoftheQueen.wav");
	//umbra::g_audioSystem.AddAudio("dead", "Explosion.wav");

	//create scene
	m_scene = std::make_unique<umbra::Scene>();
	m_scene->Load("scenes/scene.json");
	m_scene->Load("scenes/tilemap.json");
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
	
		break;

	case RectangleGug::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;

		break;

	case RectangleGug::StartLevel:
		m_scene->RemoveAll(dt);
		m_state = eState::Game;
		
		break;

	case RectangleGug::Tutorial:

			
		break;

	case RectangleGug::Game:
	
		break;
	case RectangleGug::PlayerDeadStart:
		

		break;

	case RectangleGug::PlayerDead:

		break;

	case RectangleGug::GameOverStart:
		
		break;

	case RectangleGug::GameOver:

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