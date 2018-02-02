#include "MainMenu.h"
#include "Core.h"

#include <SFGUI/Renderer.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Label.hpp>

#include "Game.h"

MainMenu::MainMenu()
{
	m_guiWindow = sfg::Window::Create();
	m_guiWindow->SetTitle("Title");

	// Create the label.
	auto label = sfg::Label::Create();

	// Set the text of the label.
	label->SetText("Hello World!\nAnother Line");

	m_guiWindow->Add(label);

	Core::getGuiDesktop()->Add(m_guiWindow);
}

void MainMenu::onInit()
{
	onReturn();
}

void MainMenu::onClose()
{
	onLeave();
}

void MainMenu::onUpdate(const float dt)
{
	if (Input::getKeyDown(Key::Return)) {
		SceneManager::addScene<Game>();
		return;
	}
}

void MainMenu::onDraw(const float dt)
{
	Core::getWindow().clear(sf::Color(30, 30, 30));

	Core::getGui()->Display(Core::getWindow());
}

void MainMenu::onLeave()
{
	m_guiWindow->Show(false);

	Log::write("loaded new scene");
}

void MainMenu::onReturn()
{
	m_guiWindow->Show(true);

	Log::write("returned to last scene");
}
