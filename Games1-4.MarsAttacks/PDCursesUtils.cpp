#include "PDCursesUtils.h"

// Wrappers to hide implementation details

void initializeCurses(bool no_delay) {
	initscr();
	curs_set(false);
	noecho(); // characters typed in are not displayed
	nodelay(stdscr, no_delay); // true means no delay - getch to not block, it's not waiting
	keypad(stdscr, true); // enables the arrow keys
}

void shutdownCurses() {
	endwin();
}

void clearScreen() {
	clear();
}

void refreshScreen() {
	refresh();
}

int screenWidth() {
	return COLS;
}

int screenHeight() {
	return LINES;
}

int getChar() {
	return getch();
}

void drawCharacter(const int& x_pos, const int& y_pos, const char& a_character) {
	mvaddch(y_pos, x_pos, a_character);
}

void moveCursor(const int& x_pos, const int& y_pos) {
	move(y_pos, x_pos);
}

void drawSprite(const int& x_pos, const int& y_pos, const std::vector<std::string>& sprite, const int& sprite_height, const int& offset) {
	for (int h = 0; h < sprite_height; h++)
	{
		mvprintw(y_pos + h, x_pos, "%s", sprite.at(h).c_str());
	}
}