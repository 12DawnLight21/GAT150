#include "Coin.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Audio/AudioSystem.h"

#include "Game/SpaceRanch.h"

namespace umbra
{
	CLASS_DEFINITION(Coin)

		bool Coin::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<umbra::PhysicsComponent>();

		return true;
	}

	void Coin::OnDestroy()
	{
		Actor::OnDestroy();
	}

	void Coin::Update(float dt)
	{
		Actor::Update(dt);

		
	}

	void Coin::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player")
		{
			//destroyed = true;
		}
	}

	void Coin::OnCollisionExit(Actor* other)
	{
		
	}

	void Coin::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speedUp);
		READ_DATA(value, speedTime);
	}
}