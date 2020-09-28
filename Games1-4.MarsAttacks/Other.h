#pragma once

// Class to add external libraries includes related with PDCurses and to contain other data structures

// define must be typed before windows.h
#define _WIN32_WINNT 0x0500 // Used to resize console window. It says that you are running this program on Windows 2000 or higher.
#include <windows.h> // Used in Game.cpp in setConsoleWindowSize()

#undef MOUSE_MOVED // To avoid macro redefinition error in curses.h because MOUSE_MOVED is also defined in windows.h
#include "curses.h"

#include "PDCursesUtils.h"

enum {
	DEF_FPS = 20,
	DEF_NUM_SHIELDS = 4,
	DEF_INI_POSITION_SHIELD_Y_OFFSET_DOWN = 2,
};

struct Position {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};