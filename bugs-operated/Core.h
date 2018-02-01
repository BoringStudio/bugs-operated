#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"
#include "CursorManager.h"
#include "SceneManager.h"
#include "FileManager.h"

#include "TextureFactory.h"
#include "AnimationFactory.h"
#include "FontFactory.h"

#include "Delegate.h"
#include "Input.h"
#include "Log.h"
#include "Time.h"

class Core
{
public:
	struct Parameters
	{
		Parameters() : title("game"), width(800), height(600), fullscreen(false), vsync(true) {}

		std::string title;
		size_t width;
		size_t height;
		bool fullscreen;
		bool vsync;
	};

	// Creates window, initializes all managers
	static void init(const Parameters& parameters);

    // Clears up all data
	static void close();

	// Starts main game loop
	static void run();

	// Stops game loop
	static void stop();

	static sf::RenderWindow& getWindow();

private:
	static void handleEvents();

	static bool m_isInitialized;
	static bool m_isRunning;

	static sf::RenderWindow m_window;
};
