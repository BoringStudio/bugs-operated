#include "Game.h"
#include "Core.h"

void Game::onInit()
{
}

void Game::onClose()
{
}

void Game::onUpdate(const float dt)
{
	if (Input::getKeyDown(Key::Escape)) {

	}
}

void Game::onDraw(const float dt)
{
	Core::getWindow().clear(sf::Color(30, 30, 30));
}
