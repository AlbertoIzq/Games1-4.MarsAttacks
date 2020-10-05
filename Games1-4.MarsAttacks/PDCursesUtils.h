#pragma once

#include <curses.h>

#include <string>
#include <vector>

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
void moveCursor(const int& x_pos, const int& y_pos);

void drawCharacter(const int& x_pos, const int& y_pos, const char& a_character);
void drawSprite(const int& x_pos, const int& y_pos, const std::vector<std::string>& sprite);
void drawString(const int& x_pos, const int& y_pos, std::string& string_text);