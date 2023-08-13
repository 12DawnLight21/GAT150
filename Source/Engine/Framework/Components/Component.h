#pragma once
#include "Framework/Object.h"

namespace umbra
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0; //takes the delta time
	
		friend class Actor;

	public:
		class Actor* m_owner = nullptr; //forward declaration + initialization
	};
}