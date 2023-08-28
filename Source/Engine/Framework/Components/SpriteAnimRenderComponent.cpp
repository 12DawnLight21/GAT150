#include "SpriteAnimRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resources/ResourceManager.h"

namespace umbra
{
		CLASS_DEFINITION(SpriteAnimComponent)

		bool SpriteAnimComponent::Initialize()
	{
		SpriteComponent::Initialize();

		SetSequence(defaultSequenceName);
		UpdateSource();

		return true;
	}

	void SpriteAnimComponent::Update(float dt)
	{
		frameTimer -= dt;
		if (frameTimer <= 0)
		{
			frameTimer = 1.0f / m_currentSequence->fps;
			frame++;

			if (frame > m_currentSequence->endFrame)
			{
				frame = (m_currentSequence->loop) ? m_currentSequence->startFrame : m_currentSequence->endFrame;
			}
		}

		UpdateSource();
	}

	void SpriteAnimComponent::SetSequence(const std::string& name)
	{
		//prevents setting sequence again
		if (m_currentSequence && m_currentSequence->name == name) return;

		if (m_sequences.find(name) != m_sequences.end())
		{
			//set new sequence
			m_currentSequence = &m_sequences[name];
			
			//set texture
			if (m_currentSequence->texture) m_texture = m_currentSequence->texture;
			//set frame information
			frame = m_currentSequence->startFrame;
			frameTimer = 1.0f / m_currentSequence->fps;
		}
	}

	void SpriteAnimComponent::UpdateSource()
	{
		vec2 cellSize = m_texture->GetSize() / vec2{ m_currentSequence->numColumns, m_currentSequence->numRows };

		int column = (frame - 1) % m_currentSequence->numColumns;
		int row = (frame - 1) / m_currentSequence->numColumns;

		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);
	}

	void SpriteAnimComponent::Read(const json_t& value)
	{
		SpriteComponent::Read(value); //reads data from parent me thinks

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray())
		{
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray())
			{
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName))
		{
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}
}