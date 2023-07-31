#include "InputSystem.h"
#include "SDL2-2.28.0/include/SDL.h"

namespace umbra
{
	InputSystem g_inputSystem;

	bool InputSystem::Initialize()
	{
		int numKeys = 0;
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys); //points to sdl keyboard states and # of keys
		m_keyboardState.resize(numKeys); //resize vector using numKeys' size
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin()); //copy sdl state to keybaord state
		m_prevKeyboardState = m_keyboardState;

		return true;
	}
	void InputSystem::Shutdown()
	{
		//empty
	}
	void InputSystem::Update()
	{
		//updates sdl events
		SDL_Event event;
		SDL_PollEvent(&event);

		//keyboard things
		m_prevKeyboardState = m_keyboardState; //saves prev state

		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr); //gets sdl keyboard state 
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin()); //copy sdl state to input system keybaord state

		//mouse things
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = Vector2{ x, y };

		m_prevMouseButtonState = m_mouseButtonState;
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; //buttons 0001 and 0RML
		m_mouseButtonState[1] = buttons & SDL_BUTTON_LMASK; //buttons 0010 and 0RML
		m_mouseButtonState[2] = buttons & SDL_BUTTON_LMASK; //buttons 0100 and 0RML

	}
}