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
	umbra::vec2 m_pos;
	umbra::vec2 m_vel;
};

int main(int argc, char* argv[])
{
	//INFO_LOG("Initializing Engine...");

	umbra::MemoryTracker::Initialize();

	umbra::seedRandom((unsigned int)time(nullptr));
	umbra::setFilePath("assets");

	//json file reading
	rapidjson::Document document;
	umbra::Json::Load("json.txt", document);
	int i1;
	umbra::Json::Read(document, "integer1", i1); //integer1 is the key in the json file, i1 is where we put that data
	std::cout << i1 << std::endl;
	int i2;
	umbra::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	std::string str;
	umbra::Json::Read(document, "string", str);
	std::cout << str << std::endl;
	bool b;
	umbra::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;
	float f;
	umbra::Json::Read(document, "float", f);
	std::cout << f << std::endl;
	umbra::vec2 v2;
	umbra::Json::Read(document, "vector2", v2);
	std::cout << v2 << std::endl;

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