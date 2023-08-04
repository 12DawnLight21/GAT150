#pragma once

namespace umbra
{
	class Component
	{
	public:
		virtual void Update(float dt) = 0; //takes the delta time
	
		friend class Actor;

	protected:
		class Actor* m_owner = nullptr; //forward declaration + initialization
	};
}