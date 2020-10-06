#pragma once

// Class to add external libraries includes related with PDCurses and to contain other data structures

// define must be typed before windows.h
#define _WIN32_WINNT 0x0500 // Used to resize console window. It says that you are running this program on Windows 2000 or higher.
#include <windows.h> // Used in Game.cpp in setConsoleWindowSize()

#undef MOUSE_MOVED // To avoid macro redefinition error in curses.h because MOUSE_MOVED is also defined in windows.h
#include "curses.h"

#include "PDCursesUtils.h"

enum {
	DEF_FPS = 30,
	DEF_NOT_IN_PLAY = -1,
	DEF_MAX_ALPHABET_CHARS = 26
};

struct Position {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};