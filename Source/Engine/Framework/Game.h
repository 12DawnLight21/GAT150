#pragma once
#include <memory>

namespace umbra
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0; 
		virtual bool Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;


		int GetScore() const { return m_score; } //variable doesnt change despite the value changing
		void AddPoints(int points) { m_score += points; } //this literally changes

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }

	protected:
		std::unique_ptr<class Scene> m_scene; //using forward declarations 

		int m_score = 0;
		int m_lives = 0;
	};
}