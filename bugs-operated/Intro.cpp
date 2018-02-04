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
	ResourceManager::bind<SoundBufferFactory>("uganda_knuck", "sounds/uganda_knuck.ogg");
	ResourceManager::bind<SoundBufferFactory>("uganda_dewey", "sounds/uganda_dewey.ogg");

	m_studioName.setFont(*ResourceManager::get<sf::Font>("arial_rounded_bold"));
	m_studioName.setCharacterSize(70);
	m_studioName.setFillColor(sf::Color::White);
	m_studioName.setString("KNUCK STUDIO");

	sf::Texture* ugandaTexture = ResourceManager::get<sf::Texture>("uganda_warrior");
	ugandaTexture->setSmooth(true);

	m_introRect.setTexture(ugandaTexture);
	m_introRect.setSize(vec2(ugandaTexture->getSize()));

	m_sound.setBuffer(*ResourceManager::get<sf::SoundBuffer>("uganda_knuck"));
	m_sound.setLoop(true);
	m_sound.play();

	float indent = 30.0f;
	m_studioName.setOrigin(std::ceil(m_studioName.getGlobalBounds().width * 0.5f), -std::ceil((m_introRect.getSize().y + indent + m_studioName.getGlobalBounds().height) * 0.5f - m_studioName.getGlobalBounds().height));
	m_introRect.setOrigin(std::ceil(m_introRect.getSize().x * 0.5f), std::ceil((m_introRect.getSize().y + indent + m_studioName.getGlobalBounds().height) * 0.5f));

	m_clearColor = sf::Color(198, 43, 41);
	m_currentClearColor = m_clearColor;

	onResize(vec2(Core::getWindow().getSize()));

	m_speedDelay = 0.2f;
	m_sinStep = 0.0f;
	m_alpha = 0.0f;
	m_blackScreenDelay = 3.0f;
	m_blackScreenDt = 0.0f;

	m_hasEnableAnimation = true;
	m_hasEnableBlackScreen = false;
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
	if (Input::getAnyKeyDown() || Input::getAnyMouseDown()) {
		SceneManager::changeScene<MainMenu>();
		return;
	}

	m_alpha = std::sin(m_sinStep);
	m_sound.setVolume(m_alpha * 100.0f);
	m_sinStep += m_speedDelay * dt;

	if (m_sinStep >= MATH_PI * 0.5f) {
		if (m_hasEnableAnimation == true) {
			m_sound.setLoop(false);
			m_sound.setVolume(100.0f);
			m_sound.setBuffer(*ResourceManager::get<sf::SoundBuffer>("uganda_dewey"));
			m_sound.play();
		}
		m_hasEnableAnimation = false;
	}
	if (m_sinStep >= MATH_PI * 0.6f || m_sound.getStatus() != sf::Sound::Status::Playing) {
		m_blackScreenDt += dt;

		if (!m_hasEnableBlackScreen) {
			m_hasEnableBlackScreen = true;
			m_currentClearColor = sf::Color::Black;
		}

		if (m_blackScreenDt >= m_blackScreenDelay) {
			SceneManager::changeScene<MainMenu>();
			return;
		}
	}
	if (m_hasEnableAnimation) {
		m_introRect.setFillColor(sf::Color(255, 255, 255, sf::Uint8(255 * m_alpha)));
		m_introRect.setScale(m_alpha + 0.5f, m_alpha + 0.5f);

		m_studioName.setFillColor(sf::Color(255, 255, 255, sf::Uint8(255 * m_alpha)));
		m_studioName.setScale(m_alpha + 0.5f, m_alpha + 0.5f);
	}
}

void Intro::onDraw(const float dt)
{
	Core::getWindow().clear(m_currentClearColor);

	if (!m_hasEnableBlackScreen) {
		Core::getWindow().draw(m_introRect);
		Core::getWindow().draw(m_studioName);
	}
}

void Intro::onResize(const vec2 & windowSize)
{
	Core::getWindow().setView(sf::View(windowSize * 0.5f, windowSize));

	m_introRect.setPosition(math::ceil(windowSize * 0.5f));
	m_studioName.setPosition(math::ceil(windowSize * 0.5f));
}

void Intro::onFocusLost()
{
}

void Intro::onFocusGained()
{
}
