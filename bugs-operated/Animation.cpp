#include "Animation.h"

Animation::Animation(const std::vector<sf::IntRect>& frames, const std::string& spriteSheetName) :
    m_frames(frames), m_spriteSheetName(spriteSheetName)
{
}

size_t Animation::getFrameCount() const
{
    return m_frames.size();
}

sf::IntRect Animation::getFrame(size_t n) const
{
    size_t frameCount = m_frames.size();
    if (frameCount == 0) {
        return sf::IntRect();
    }
    else {
        return m_frames[n % frameCount];
    }
}

std::string Animation::getSpriteSheetName() const
{
    return m_spriteSheetName;
}
