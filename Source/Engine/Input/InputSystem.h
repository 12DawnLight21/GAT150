#pragma once
#include <array>
#include <vector>
#include "Core/Core.h"

namespace umbra
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool getKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		bool getPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }

		const Vector2& GetMousePosition() const { return m_mousePosition; };

		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; };
		bool GetMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; };
		
	private:
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

		Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState; //maple has these as arrays but making them vectors made the red go away lol
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern InputSystem g_inputSystem;
}