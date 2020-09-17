#include "curses.h"
#include "StaticLib-Utils.h"

// define must be typed before windows.h; curses.h must be typed before both
#define _WIN32_WINNT 0x0500 // Used to resize console window. It says that you are running this program on Windows 2000 or higher.
#include <windows.h>

#include <iostream>

void SetConsoleWindowSize();

int main(void)
{
    //SetConsoleWindowSize();
    return 0;
}

void SetConsoleWindowSize() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    //int width{ r.right - r.left };
    //int height{ r.bottom - r.top};
    // MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, 607, 550, TRUE); // Values get by setting console size manually when running the program
}