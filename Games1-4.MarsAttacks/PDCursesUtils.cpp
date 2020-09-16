#include "PDCursesUtils.h"

// Wrappers to hide implementation details

void InitializeCurses(bool no_delay) {
	initscr();
	curs_set(false);
	noecho(); // characters typed in are not displayed
	nodelay(stdscr, no_delay); // true means no delay - getch to not block, it's not waiting
	keypad(stdscr, true); // enables the arrow keys
}

void ShutdownCurses() {
	endwin();
}

void ClearScreen() {
	clear();
}

void RefreshScreen() {
	refresh();
}

int ScreenWidth() {
	return COLS;
}

int ScreenHeight() {
	return LINES;
}

int GetChar() {
	return getch();
}

void DrawCharacter(int x_pos, int y_pos, char a_character) {
	mvaddch(y_pos, x_pos, a_character);
}

void MoveCursor(int x_pos, int y_pos) {
	move(y_pos, x_pos);
}