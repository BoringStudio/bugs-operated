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
	m_translate = vec2(-1000.0f, -1000.0f);

	onResize(vec2(Core::getWindow().getSize()));
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
	Core::getWindow().clear(m_map->getBackgroundColor());

	if (Input::getKey(Key::A)) {
		m_translate += vec2(300.0f, 0.0f) * dt;
	}
	else if (Input::getKey(Key::D)) {
		m_translate -= vec2(300.0f, 0.0f) * dt;
	}

	if (Input::getKey(Key::W)) {
		m_translate += vec2(0.0f, 300.0f) * dt;
	}
	else if (Input::getKey(Key::S)) {
		m_translate -= vec2(0.0f, 300.0f) * dt;
	}

	sf::RenderStates states;
	states.transform.translate(m_translate);
	Core::getWindow().draw(*m_map, states);
}

void Game::onResize(const vec2& windowSize)
{
	Core::getWindow().setView(sf::View(windowSize * 0.5f, windowSize * 0.25f));
}