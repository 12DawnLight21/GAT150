#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

#include "Framework/Events/Event.h"
#include "Framework/Events/EventManager.h"

class SpaceRanch : public umbra::Game, public umbra::IEventListener
{
public:
	enum eState
	{
		Title,
		StartGame,
		StartLevel,
		Tutorial,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

public:
	virtual bool Initialize() override;
	virtual bool Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(umbra::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	virtual void OnAddPoints(const umbra::Event& event);
	void OnPlayerDead(const umbra::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 2.5f; //every 3 secs, spawn enemy

	float m_powerTimer = 0;
	float m_powerTime = 8.0f; //every 8 secs, spawn powerup

	float m_stateTimer = 0;

	std::shared_ptr<umbra::Font> m_font;
	std::unique_ptr<umbra::Text> m_scoreText;
	std::unique_ptr<umbra::Text> m_lifeText;
	std::unique_ptr<umbra::Text> m_tutorialText;
	std::unique_ptr<umbra::Text> m_tutorialText2;
	std::unique_ptr<umbra::Text> m_titleText;
	std::unique_ptr<umbra::Text> m_gameOverText;
};