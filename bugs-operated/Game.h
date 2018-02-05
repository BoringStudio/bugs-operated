#pragma once

#include "SceneManager.h"
#include "Map.h"

class Game : public Scene
{
public:
	void onInit() override;

	void onClose() override;

	void onUpdate(const float dt) override;

	void onDraw(const float dt) override;

	void onResize(const vec2& windowSize) override;

private:
	Map * m_map;
	sf::Vector2f m_translate;
};