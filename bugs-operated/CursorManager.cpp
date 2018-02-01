#include "CursorManager.h"

sf::WindowHandle CursorManager::m_windowHandle = 0;

#ifdef _WIN32
std::vector<HCURSOR> CursorManager::m_cursorIcons(TYPE_COUNT);
#elif defined(__linux__)
std::vector<XID> CursorManager::m_cursorIcons(TYPE_COUNT);
Display* CursorManager::m_display = nullptr;
#endif

void CursorManager::init(const sf::WindowHandle & window_handle)
{
	m_windowHandle = window_handle;

#ifdef _WIN32
	m_cursorIcons[Type::WAIT] = LoadCursor(NULL, IDC_WAIT);
	m_cursorIcons[Type::HAND] = LoadCursor(NULL, IDC_HAND);
	m_cursorIcons[Type::NORMAL] = LoadCursor(NULL, IDC_ARROW);
	m_cursorIcons[Type::TEXT] = LoadCursor(NULL, IDC_IBEAM);
#elif defined(__linux__)
	m_display = XOpenDisplay(nullptr);
	m_cursorIcons[Type::WAIT] = XCreateFontCursor(m_display, XC_watch);
	m_cursorIcons[Type::HAND] = XCreateFontCursor(m_display, XC_hand1);
	m_cursorIcons[Type::NORMAL] = XCreateFontCursor(m_display, XC_left_ptr);
	m_cursorIcons[Type::TEXT] = XCreateFontCursor(m_display, XC_xterm);
#endif
}

void CursorManager::close()
{
#ifdef __linux__
	for (unsigned int i = 0; i < TYPE_COUNT; ++i) {
		XFreeCursor(m_display, m_cursorIcons[i]);
	}
	delete m_display;
	m_display = nullptr;
#endif
}

void CursorManager::setStyle(const Type type)
{
#ifdef _WIN32
	SetClassLongPtr(m_windowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(m_cursorIcons[type]));
#elif defined(__linux__)
	XDefineCursor(m_display, m_windowHandle, m_cursorIcons[type]);
	XFlush(m_display);
#endif
}