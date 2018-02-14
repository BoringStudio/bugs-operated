#include "Game.h"
#include "Core.h"

#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Box.hpp>

void Game::onInit()
{
	m_socket = UDT::socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(7742);
	address.sin_addr.S_un.S_addr = INADDR_ANY;
	memset(&(address.sin_zero), '\0', 8);

	if (UDT::ERROR == UDT::bind(m_socket, (sockaddr*)&address, sizeof(address)))
	{
		Log::write("bind:", UDT::getlasterror().getErrorMessage());
	}

	UDT::listen(m_socket, 10);

	ResourceManager::bind<MapFactory>("planet_base", "maps/planet_base.json");

	ResourceManager::bind<ShaderFactory>("shader", 
		ShaderFactory::FromFile{ "shaders/quad.vert" }, 
		ShaderFactory::FromFile{ "shaders/scanlines.frag" });

	m_map = ResourceManager::get<Map>("planet_base");
	m_translate = vec2(-1000.0f, -1000.0f);

	m_scanlinesShader = ResourceManager::get<sf::Shader>("shader");

	onResize(vec2(Core::getWindow().getSize()));
}

void Game::onClose()
{
	UDT::close(m_socket);
}

void Game::onUpdate(const float dt)
{
	if (Input::getKeyDown(Key::Escape)) {
		SceneManager::deleteScene();
		return;
	}

	vec2 vector;
	if (Input::getKey(Key::A)) {
		vector += vec2(1.0f, 0.0f);
	}
	else if (Input::getKey(Key::D)) {
		vector -= vec2(1.0f, 0.0f);
	}

	if (Input::getKey(Key::W)) {
		vector += vec2(0.0f, 1.0f);
	}
	else if (Input::getKey(Key::S)) {
		vector -= vec2(0.0f, 1.0f);
	}
	m_translate += vector * 150.0f * dt;

	vec2 halfSize = vec2(Core::getWindow().getSize()) * 0.5f;
	rect windowBounds(halfSize * 0.5f - m_translate, halfSize);
	m_map->cull(windowBounds);
}

void Game::onDraw(const float dt)
{
	// render scene to texture
	m_frameBuffer.clear(m_map->getBackgroundColor());
	
	sf::RenderStates states;
	states.transform.translate(m_translate);
	m_frameBuffer.draw(*m_map, states);

	m_frameBuffer.display();


	// render texture
	sf::Shader::bind(m_scanlinesShader);
	Core::getWindow().draw(m_frameRectangle);
	sf::Shader::bind(nullptr);
}

void Game::onResize(const vec2& windowSize)
{
	vec2 halfSize = windowSize * 0.5f;

	// properly resizing
	Core::getWindow().setView(sf::View(halfSize, windowSize));

	// framebuffer initialization
	m_frameBuffer.create(static_cast<unsigned int>(windowSize.x), static_cast<unsigned int>(windowSize.y));
	m_frameRectangle.setSize(windowSize);
	m_frameRectangle.setTexture(&m_frameBuffer.getTexture(), true);

	m_frameBuffer.setView(sf::View(halfSize, halfSize));
}