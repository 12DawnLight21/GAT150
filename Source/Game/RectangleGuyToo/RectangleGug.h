#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

#include "Framework/Events/Event.h"
#include "Framework/Events/EventManager.h"

class RectangleGug : public umbra::Game, public umbra::IEventListener
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
	float m_spawnTime = 2.5f;

	float m_powerTimer = 0;
	float m_powerTime = 8.0f;
};