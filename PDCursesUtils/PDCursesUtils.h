#pragma once

#include <curses.h>

enum ArrowKeys {
	UP = KEY_UP,
	DOWN = KEY_DOWN,
	LEFT = KEY_LEFT,
	RIGHT = KEY_RIGHT
};

void InitializeCurses(bool no_delay);
void ShutdownCurses();
void ClearScreen();
void RefreshScreen();

int ScreenWidth();
int ScreenHeight();
int GetChar();
void DrawCharacter(int x_pos, int y_pos, char a_character);
void MoveCursor(int x_pos, int y_pos);