#include "Games1-4.MarsAttacks.h"

int main(void)
{
    SetConsoleWindowSize();
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
