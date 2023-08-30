#pragma once
#include "SpriteComponent.h"

namespace umbra
{
    class SpriteAnimComponent : public SpriteComponent
    {
    public:
        struct AnimSequence
        {
            std::string name;

            float fps = 0;         // Frames per second of the animation
            int numColumns = 0;    // Number of columns in the sprite sheet
            int numRows = 0;       // Number of rows in the sprite sheet

            int startFrame = 0;    // Starting frame of the sequence
            int endFrame = 0;      // Ending frame of the sequence

            bool loop = true;      // Whether the animation should loop

            std::shared_ptr<Texture> texture;  // Pointer to the texture used for this sequence
        };

    public:
        CLASS_DECLARATION(SpriteAnimComponent)

        bool Initialize() override;
        void Update(float dt);

        void SetSequence(const std::string& name, bool update = true);
        void UpdateSource();

    public:
        int frame = 0;           // Current frame of the animation
        float frameTimer = 0;    // Timer for controlling frame updates

    private:
        std::string defaultSequenceName;

        std::map<std::string, AnimSequence> m_sequences;

        AnimSequence* m_currentSequence = nullptr;
    };
}