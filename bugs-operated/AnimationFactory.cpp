#include "AnimationFactory.h"

#include <json.hpp>

#include "FileManager.h"

using json = nlohmann::json;

AnimationFactory::AnimationFactory(const std::string& filename) :
    AbstractFactory(tag<Animation>{}), m_data(nullptr),
    m_filename(filename)
{
}

void* AnimationFactory::load()
{
    if (m_data == nullptr) {
        std::vector<sf::IntRect> frames;
        std::string spriteSheetName;

        json animationData;

        {
            std::vector<char> data = FileManager::open(m_filename);
            animationData = json::parse(data.begin(), data.end());
        }

        json framesData = animationData["frames"];
        if (framesData.is_array()) {
            for (const auto& frameData : framesData) {
                if (frameData.is_object()) {
                    sf::IntRect frame;
                    
                    json xData = frameData["x"];
                    if (xData.is_number_integer()) {
                        frame.left = xData;
                    }
                    
                    json yData = frameData["y"];
                    if (yData.is_number_integer()) {
                        frame.top = yData;
                    }
                    
                    json wData = frameData["w"];
                    if (wData.is_number_integer()) {
                        frame.width = wData;
                    }
                    
                    json hData = frameData["h"];
                    if (hData.is_number_integer()) {
                        frame.height = hData;
                    }
                    
                    frames.push_back(frame);
                }
            }
        }
        
        json metaData = animationData["meta"];
        if (metaData.is_object()) {
            json imageData = metaData["image"];
            if (imageData.is_string()) {
                spriteSheetName = imageData;
            }
        }
        
        if (frames.size() != 0 && !spriteSheetName.empty()) {
            m_data = std::make_unique<Animation>(frames, spriteSheetName);
        }
        else {
            throw std::runtime_error("Bad animation file: \"" + m_filename + "\"");
        }
    }
    
    return m_data.get();
}

void AnimationFactory::clear()
{
    m_data.reset(nullptr);
}
