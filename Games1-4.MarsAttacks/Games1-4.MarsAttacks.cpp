#include <string>
#include "curses.h"

using std::string;

int main()
{
	initscr(); // to initialize pdcurses
	curs_set(false); // Makes the cursor invisible

	//move(15, 10); // changes cursor position (y axis, x axis)
	//printw("Hello World!!!");
	mvprintw(15, 10, "Hello World!!!"); // uses c string

	string helloString = "Hello World";
	mvprintw(15, 10, helloString.c_str());

	// LINES is the number of rows of our window
	// COLS is the number of columns

	mvprintw(LINES / 2, COLS / 2, "Hello World!");

	int windowMaxX = 0;
	int windowMaxY = 0;

	getmaxyx(stdscr, windowMaxY, windowMaxX); // Would have the same value has LINES and COLS

	//addch('*'); // To draw just a character
	mvaddch(15, 10, '*');

	clear(); // clears the entire screen

	refresh(); // to show what we have printed
	getch(); // get one character from the user, to pause
	endwin(); // cleans the screen, to end pdcurses mode

	return 0;
}