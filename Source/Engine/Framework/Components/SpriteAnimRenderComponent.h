#pragma once
#include "SpriteComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace umbra
{
	class SpriteAnimComponent : public SpriteComponent
	{
	public:
		CLASS_DECLARATION(SpriteAnimComponent)

		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

	public:
		bool Initialize() override;
		void Update(float dt);

		void SetSequence(const std::string& name);
		void UpdateSource();

	public:
		int frame = 0;
		float frameTimer = 0;

	private:
		std::string defaultSequenceName; //what we wanna play at the beginning
		std::map<std::string, AnimSequence> m_sequences;

		AnimSequence* m_currentSequence = nullptr;
	};
}