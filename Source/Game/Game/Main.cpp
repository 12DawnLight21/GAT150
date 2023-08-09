#include "SpaceRanch.h"
#include "Player.h"
#include "Enemy.h"

#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"

#include <thread>
#include <iostream> //searches the system instead
#include <vector>

using namespace std;

class Star
{
public:
	Star(const umbra::Vector2& pos, const umbra::Vector2& vel):
		m_pos{pos},
		m_vel{vel}
	{}

	void Update()
	{
		m_pos += m_vel * umbra::g_time.GetDeltaTime();
	}

	void Draw(umbra::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	umbra::vec3 m_pos;
	umbra::vec3 m_vel;
};

/*
void print_arg(int count, ...) //after count is where we start the va arg
{
	va_list args;

	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}
void zero(int v) //pass by copy or pass by value
{
	//makes a deep copy of the value
	v = 0;
}
void zero(int* v) //pass by pointer
{
	*v = 0; //use & to pass reference OF value
}
void zero_ref(int& v) //pass by reference (used if answer COULD be NULL)
{
	//if literal value, needs to take in a const int&
	v = 0;
}

void print(const std::string& s) //if we dont change value, make it const ;3
{
	//if we took a value, it would copy the og value first
	cout << s << endl;
}
*/

int main(int argc, char* argv[])
{

	//click on things and press f12 to see what it is / does (i think ctrl-click does the same thing)
	INFO_LOG("Initializing Engine...");

	umbra::MemoryTracker::Initialize();

	umbra::seedRandom((unsigned int)time(nullptr));
	umbra::setFilePath("assets");

	//our window setup
	umbra::g_renderer.Initialize();
	umbra::g_renderer.CreateWindow("GAT150", 800, 600);

	umbra::g_inputSystem.Initialize();
	umbra::g_audioSystem.Initialize();

	unique_ptr<SpaceRanch> game = make_unique<SpaceRanch>();
	game->Initialize();

	umbra::g_audioSystem.PlayOneShot("bg_music", true); //song is The Hand of the Queen from the game Rectangle Guy

	vector<Star> stars; 
	for (int i = 0; i < 500; i++)
	{
		umbra::Vector2 pos(umbra::Vector2(umbra::random(umbra::g_renderer.GetWidth()), umbra::random(umbra::g_renderer.GetHeight())));
		umbra::Vector2 vel(umbra::randomf(1, 8), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	bool quit = false;
	// Main GAME LOOP
	while (!quit)
	{
		//update engine
		umbra::g_time.Tick();
		umbra::g_inputSystem.Update(); //checks for input updates 
		umbra::g_audioSystem.Update(); //updates the audio systems
		umbra::g_particleSystem.Update(umbra::g_time.GetDeltaTime());

		//update game
		game->Update(umbra::g_time.GetDeltaTime());

		umbra::g_renderer.SetColor(0, 0, 0, 0); //sets color to black
		umbra::g_renderer.BeginFrame(); //clears the screen, allows for less static

		if (umbra::g_inputSystem.getKeyDown(SDL_SCANCODE_ESCAPE)) //if esc is pressed, end the thing
		{
			quit = true;
		}

		//update draw
		umbra::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars) 
		{
			star.Update();

			if (star.m_pos.x >= umbra::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= umbra::g_renderer.GetHeight()) star.m_pos.y = 0;

			umbra::g_renderer.SetColor(umbra::random(256), umbra::random(256), umbra::random(256), 255);
			umbra::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		game->Draw(umbra::g_renderer);

		umbra::g_renderer.EndFrame();
	}

	stars.clear();

	return 0; 
}

// LNK errors are linking errors