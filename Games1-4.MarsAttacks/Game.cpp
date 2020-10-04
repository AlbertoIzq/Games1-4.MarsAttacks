#include "Game.h"

const Size Game::DEF_WINDOW_SIZE{ DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT };

Game::Game()
    : windowSize{ DEF_WINDOW_SIZE }, currentState{ DEF_GAME_STATE }, level{ DEF_LEVEL }, waitTimer{ DEF_WAIT_TIMER } {
    setConsoleWindowSize();
}

void Game::setConsoleWindowSize() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions  
    int width{ r.right - r.left }; // Used to get width and height in pixels
    int height{ r.bottom - r.top};
    // MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, DEF_WINDOW_WIDTH_PIXELS, DEF_WINDOW_HEIGHT_PIXELS, TRUE);
}