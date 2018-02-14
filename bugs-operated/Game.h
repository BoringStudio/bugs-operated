#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "SceneManager.h"
#include "Map.h"

#include <UDT/udt.h>

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

	sf::RectangleShape m_frameRectangle;
	sf::RenderTexture m_frameBuffer;

	sf::Shader* m_scanlinesShader;

	UDTSOCKET m_socket;
};