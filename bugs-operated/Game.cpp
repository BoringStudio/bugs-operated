#include "Game.h"
#include "Core.h"

#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Box.hpp>

void Game::onInit()
{
	ResourceManager::bind<MapFactory>("planet_base", "maps/planet_base.json");

	m_map = ResourceManager::get<Map>("planet_base");
}

void Game::onClose()
{
}

void Game::onUpdate(const float dt)
{
	if (Input::getKeyDown(Key::Escape)) {
		SceneManager::deleteScene();
		return;
	}
}

void Game::onDraw(const float dt)
{
	Core::getWindow().clear(sf::Color(30, 30, 30));
}
