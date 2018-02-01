#pragma once

#include <bitset>
#include <SFML/Window.hpp>

#include "Math.h"

using Key = sf::Keyboard::Key;
using MouseButton = sf::Mouse::Button;

class Input
{
public:
	static void reset();

	static bool getKey(Key keyCode);
	static bool getKeyDown(Key keyCode);
	static bool getKeyUp(Key keyCode);

	static bool getMouse(MouseButton mouseCode);
	static bool getMouseDown(MouseButton mouseCode);
	static bool getMouseUp(MouseButton mouseCode);

	static void setMousePosition(const vec2& pos);
	static vec2 getMousePosition();
	static vec2 getMouseDeltaPosition();

	static void setCursorVisible(bool visible);

private:
	friend class Core;

	static std::bitset<Key::KeyCount> m_currentKeyStates;
	static std::bitset<Key::KeyCount> m_lastKeyStates;

	static std::bitset<MouseButton::ButtonCount> m_currentMouseStates;
	static std::bitset<MouseButton::ButtonCount> m_lastMouseStates;

	static sf::Vector2i m_currentCursorPosition;
	static sf::Vector2i m_lastCursorPosition;
};
