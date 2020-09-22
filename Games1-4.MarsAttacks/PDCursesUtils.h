#pragma once

#include <curses.h>

#include <string>

enum ArrowKeys {
	AK_UP = KEY_UP,
	AK_DOWN = KEY_DOWN,
	AK_LEFT = KEY_LEFT,
	AK_RIGHT = KEY_RIGHT
};

void initializeCurses(bool no_delay);
void shutdownCurses();
void clearScreen();
void refreshScreen();

int screenWidth();
int screenHeight();
int getChar();
void drawCharacter(const int& x_pos, const int& y_pos, const char& a_character);
void moveCursor(const int& x_pos, const int& y_pos);

template<size_t N>
void drawSprite(const int& x_pos, const int& y_pos, const std::array<std::string, N>& sprite, const int& sprite_height, const int& offset = 0) {
	for (size_t h = 0; h < sprite_height; h++)
	{
		mvprintw(y_pos + h, x_pos, "%s", sprite.at(h).c_str());
	}
}