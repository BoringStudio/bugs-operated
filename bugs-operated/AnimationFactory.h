#pragma once

#include <memory>

#include "Animation.h"

#include "AbstractFactory.h"

class AnimationFactory : public AbstractFactory
{
public:
    AnimationFactory(const std::string& filename);

    void* load() override;
    void clear() override;

private:
    std::string m_filename;

    std::unique_ptr<Animation> m_data;
};
