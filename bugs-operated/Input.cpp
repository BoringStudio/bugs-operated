#include "Input.h"

#include "Core.h"

std::bitset<Key::KeyCount> Input::m_currentKeyStates;
std::bitset<Key::KeyCount> Input::m_lastKeyStates;

std::bitset<MouseButton::ButtonCount> Input::m_currentMouseStates;
std::bitset<MouseButton::ButtonCount> Input::m_lastMouseStates;

sf::Vector2i Input::m_currentCursorPosition = sf::Mouse::getPosition();
sf::Vector2i Input::m_lastCursorPosition = sf::Mouse::getPosition();

void Input::reset()
{
	m_lastKeyStates = m_currentKeyStates;
	m_lastMouseStates = m_currentMouseStates;
	m_lastCursorPosition = m_currentCursorPosition;
}

bool Input::getKey(Key keyCode)
{
	if (keyCode < Key::KeyCount) {
		return m_currentKeyStates.test(static_cast<size_t>(keyCode));
	}
	else {
		return false;
	}
}

bool Input::getKeyDown(Key keyCode)
{
	if (keyCode < Key::KeyCount) {
		return !m_lastKeyStates.test(static_cast<size_t>(keyCode)) && 
				m_currentKeyStates.test(static_cast<size_t>(keyCode));
	}
	else {
		return false;
	}
}

bool Input::getKeyUp(Key keyCode)
{
	if (keyCode < Key::KeyCount) {
		return m_lastKeyStates.test(static_cast<size_t>(keyCode)) && 
				!m_currentKeyStates.test(static_cast<size_t>(keyCode));
	}
	else {
		return false;
	}
}

bool Input::getMouse(MouseButton mouseCode)
{
	if (mouseCode < MouseButton::ButtonCount) {
		return m_currentMouseStates.test(static_cast<size_t>(mouseCode));
	}
	else {
		return false;
	}
}

bool Input::getMouseDown(MouseButton mouseCode)
{
	if (mouseCode < MouseButton::ButtonCount) {
		return !m_lastMouseStates.test(static_cast<size_t>(mouseCode)) && 
				m_currentMouseStates.test(static_cast<size_t>(mouseCode));
	}
	else {
		return false;
	}
}

bool Input::getMouseUp(MouseButton mouseCode)
{
	if (mouseCode < MouseButton::ButtonCount) {
		return m_lastMouseStates.test(static_cast<size_t>(mouseCode)) && 
				!m_currentMouseStates.test(static_cast<size_t>(mouseCode));
	}
	else {
		return false;
	}
}

void Input::setMousePosition(const vec2 & pos)
{
	m_currentCursorPosition = sf::Vector2i(static_cast<int>(pos.x), static_cast<int>(pos.y));
	sf::Mouse::setPosition(m_currentCursorPosition, Core::getWindow());
}

vec2 Input::getMousePosition()
{
	return vec2(static_cast<float>(m_currentCursorPosition.x), 
		static_cast<float>(m_currentCursorPosition.y));
}

vec2 Input::getMouseDeltaPosition()
{
	sf::Vector2i temp = m_currentCursorPosition - m_lastCursorPosition;
	return vec2(static_cast<float>(temp.x), static_cast<float>(temp.y));
}

void Input::setCursorVisible(bool visible)
{
	Core::getWindow().setMouseCursorVisible(visible);
}
