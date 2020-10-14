#pragma once

// Class to add external libraries includes related with PDCurses and to contain other data structures

#include "curses.h"
#include "PDCursesUtils.h"

enum {
	DEF_FPS = 30,
	DEF_NOT_IN_PLAY = -1,
	DEF_MAX_ALPHABET_CHARS = 26,
	DEF_MAX_SCORES = 10
};

struct Position {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};