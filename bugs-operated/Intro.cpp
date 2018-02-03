#include "Intro.h"
#include "Core.h"

#include "MainMenu.h"

Intro::Intro()
{
}

void Intro::onInit()
{
	ResourceManager::bind<TextureFactory>("uganda_warrior", "textures/uganda_warrior.png");
	ResourceManager::bind<FontFactory>("arial_rounded_bold", "fonts/arial_rounded_bold.ttf");

	m_studioName.setFont(*font);
	m_studioName.setCharacterSize(70);
	m_studioName.setFillColor(sf::Color::White);
	m_studioName.setString("KNUCK STUDIO");

	sf::Texture* ugandaTexture = ResourceManager::get<sf::Texture>("uganda_warrior");
	ugandaTexture->setSmooth(true);

	m_introRect.setTexture(ugandaTexture);
	m_introRect.setSize(vec2(ugandaTexture->getSize()));


	m_studioName.setOrigin(std::ceil(m_studioName.getGlobalBounds().width * 0.5f), 0.0f);
	m_introRect.setOrigin(math::ceil(m_introRect.getSize() * 0.5f));

	m_clearColor = sf::Color(198, 43, 41);

	onResize(vec2(Core::getWindow().getSize()));

	m_speedDelay = 0.2f;
	m_sinStep = 0.0f;
	m_alpha = 0.0f;
	m_blackScreenDelay = 3.0f;
	m_blackScreenDt = 0.0f;
	m_hasEnableAnimation = true;
}

void Intro::onClose()
{
}

void Intro::onLeave()
{
}

void Intro::onReturn()
{
}

void Intro::onUpdate(const float dt)
{
	m_alpha = std::sin(m_sinStep);
	m_sinStep += m_speedDelay * dt;

	if (m_sinStep >= MATH_PI * 0.5f)
	{
		m_hasEnableAnimation = false;
	}
	if (m_sinStep >= MATH_PI * 0.7f) {
		m_blackScreenDt += dt;

		m_introRect.setFillColor(sf::Color::Black);
		m_studioName.setFillColor(sf::Color::Black);
		m_clearColor = sf::Color::Black;

		if (m_blackScreenDt >= m_blackScreenDelay) {
			SceneManager::changeScene<MainMenu>();
		}
	}
	if (m_hasEnableAnimation) {
		m_introRect.setFillColor(sf::Color(255, 255, 255, 255 * m_alpha));
		m_introRect.setScale(m_alpha + 0.5f, m_alpha + 0.5f);

		m_studioName.setScale(m_alpha + 0.5f, m_alpha + 0.5f);
	}
}

void Intro::onDraw(const float dt)
{
	Core::getWindow().clear(m_clearColor);
	Core::getWindow().draw(m_introRect);
	Core::getWindow().draw(m_studioName);
}

void Intro::onResize(const vec2 & windowSize)
{
	Core::getWindow().setView(sf::View(windowSize * 0.5f, windowSize));

	m_introRect.setPosition(math::ceil(windowSize * 0.5f));
	m_studioName.setPosition(math::ceil(vec2(windowSize.x * 0.5f, windowSize.y - 100.0f)));
}

void Intro::onFocusLost()
{
}

void Intro::onFocusGained()
{
}
