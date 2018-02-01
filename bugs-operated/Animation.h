#pragma once

#include <vector>

#include "Math.h"

// Sprite animation data
class Animation
{
public:
    Animation(const std::vector<sf::IntRect>& frames, const std::string& spriteSheetName);

    size_t getFrameCount() const;
    sf::IntRect getFrame(size_t n) const;
    std::string getSpriteSheetName() const;

private:
    std::vector<sf::IntRect> m_frames;
    std::string m_spriteSheetName;
};
