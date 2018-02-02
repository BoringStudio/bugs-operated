#include "Game.h"
#include "Core.h"

#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Box.hpp>

void Game::onInit()
{
	m_guiWindow = sfg::Window::Create();
	m_guiWindow->SetTitle("Axcvxcv");

	// Create the label.
	auto label = sfg::Label::Create();

	// Set the text of the label.
	label->SetText("Hasdasdasde");

	m_guiWindow->Add(label);

	Core::getGuiDesktop()->Add(m_guiWindow);
}

void Game::onClose()
{
	Core::getGuiDesktop()->Remove(m_guiWindow);
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

	Core::getGui()->Display(Core::getWindow());
}
