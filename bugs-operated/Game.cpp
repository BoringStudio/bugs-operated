#include "Game.h"
#include "Core.h"

#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Box.hpp>

void Game::onInit()
{
	ResourceManager::bind<MapFactory>("planet_base", "maps/planet_base.json");

	std::string vertexShader = 
R"(void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
)";

	std::string fragmentShader =
R"(uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	if (mod(gl_FragCoord.y, 2.0) >= 1) {
		color *= vec4(0.9);
	}
    else {
        color *= vec4(1.05);
	}

    gl_FragColor = color * gl_Color;
}
)";

	ResourceManager::bind<ShaderFactory>("shader", ShaderFactory::FromString{ vertexShader }, ShaderFactory::FromString{ fragmentShader });

	m_map = ResourceManager::get<Map>("planet_base");
	m_translate = vec2(-1000.0f, -1000.0f);

	m_scanlinesShader = ResourceManager::get<sf::Shader>("shader");

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
	m_frameBuffer.create(windowSize.x, windowSize.y);
	m_frameRectangle.setSize(windowSize);
	m_frameRectangle.setTexture(&m_frameBuffer.getTexture(), true);

	m_frameBuffer.setView(sf::View(halfSize, halfSize));
}