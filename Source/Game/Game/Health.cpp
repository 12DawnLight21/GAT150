#include "Health.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Audio/AudioSystem.h"

#include "SpaceRanch.h"

void Health::Update(float dt)
{
	Actor::Update(dt);
	//not sure exactly what goes here yet lol

}

void Health::OnCollisionEnter(Actor* other)
{
	if (other->tag == "Player")
	{
		//create explosion
		umbra::EmitterData data;
		data.burst = true;
		data.burstCount = 50;
		data.spawnRate = 0;
		data.angle = 2;
		data.angleRange = umbra::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 25;
		data.speedMax = 200;
		data.damping = 0.6f;
		data.color = umbra::Color{ 0, 0.5531145f, 1,  1 };

		/*umbra::Transform transform{transform.position, 0, 1};
		auto emitter = std::make_unique<umbra::Emitter>(transform, data);
		emitter->SetLifespan(0.1f);
		m_scene->Add(std::move(emitter));

		m_game->AddPoints(getValue(m_minValue, m_maxValue) * 250);
		m_destroyed = true;

		umbra::g_audioSystem.PlayOneShot("power", false);
		dynamic_cast<SpaceRanch*>(m_game)->SetState(SpaceRanch::eState::Game);*/
	}
}
