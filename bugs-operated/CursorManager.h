#pragma once

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef _WIN32
#include <windows.h>

#ifdef SendMessage
#undef SendMessage
#endif
#elif defined(__linux__)
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#endif

class CursorManager
{
public:
	enum Type { 
		WAIT, 
		TEXT, 
		NORMAL, 
		HAND,

		TYPE_COUNT
	};

	static void init(const sf::WindowHandle& window_handle);
	static void close();

	static void setStyle(const Type type);
private:
	static sf::WindowHandle m_windowHandle;

#ifdef SFML_SYSTEM_WINDOWS
	static std::vector<HCURSOR> m_cursorIcons;
#else
	static std::vector<XID> m_cursorIcons;
	static Display* m_display;
#endif
};