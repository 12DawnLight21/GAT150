#include "RectangleGug.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"

#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	//INFO_LOG("Initializing Engine...");

	umbra::MemoryTracker::Initialize();

	umbra::seedRandom((unsigned int)time(nullptr));
	umbra::setFilePath("assets");

	//our window setup
	umbra::g_renderer.Initialize();
	umbra::g_renderer.CreateWindow("GAT150", 800, 600);

	umbra::g_inputSystem.Initialize();
	umbra::g_audioSystem.Initialize();
	umbra::PhysicsSystem::Instance().Initialize();

	unique_ptr<RectangleGug> game = make_unique<RectangleGug>();
	game->Initialize();

	//umbra::g_audioSystem.PlayOneShot("bg_music", true); //song is The Hand of the Queen from the game Rectangle Guy

	bool quit = false;
	// Main GAME LOOP
	while (!quit)
	{
		//update engine
		umbra::g_time.Tick();
		umbra::g_inputSystem.Update();
		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_ESCAPE)) //if esc is pressed, end the thing
		{
			quit = true;
		}

		//umbra::g_audioSystem.Update();
		umbra::g_particleSystem.Update(umbra::g_time.GetDeltaTime());

		umbra::PhysicsSystem::Instance().Update(umbra::g_time.GetDeltaTime());

		//update game
		game->Update(umbra::g_time.GetDeltaTime());

		umbra::g_renderer.SetColor(0, 0, 0, 0); //sets color to black

		umbra::g_renderer.BeginFrame();
		
		//update draw

		game->Draw(umbra::g_renderer);

		umbra::g_renderer.EndFrame();
	}

	return 0;
}