#include "Game.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const Size Game::DEF_WINDOW_SIZE{ DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT };

Game::Game()
    : windowSize{ DEF_WINDOW_SIZE }, currentState{ DEF_GAME_STATE }, level{ DEF_LEVEL }, waitTimer{ DEF_WAIT_TIMER },
    playerNameHPositionCursor{0 } {
    setConsoleWindowSize();

    for (int i{ 0 }; i < DEF_MAX_CHAR_NAME_SCORE; i++) {
        playerName += 'A';
        playerNameVPositionCursor.push_back(0); // Be at 'A'
    }
}

void Game::setConsoleWindowSize() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions  
    int width{ r.right - r.left }; // Used to get width and height in pixels to feed manually class constants
    int height{ r.bottom - r.top};
    // MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, DEF_WINDOW_WIDTH_PIXELS, DEF_WINDOW_HEIGHT_PIXELS, TRUE);
}

void Game::resetLevel() {
    waitTimer = DEF_WAIT_TIMER;
}

void Game::resetAll() {
    resetLevel();
    level = DEF_LEVEL;
}

void Game::drawPlayerName(const int& pos_x, const int& pos_y) const {
    for (int i{ 0 }; i < DEF_MAX_CHAR_NAME_SCORE; i++) {
        if (i == playerNameHPositionCursor) {
            setBrightBackText();
        }
        drawCharacter(pos_x + i, pos_y, playerName.at(i));
        if (i == playerNameHPositionCursor) {
            unsetBrightBackText();
        }
    }
}

void Game::moveNameLetterRight() {
    playerNameHPositionCursor = (playerNameHPositionCursor + 1) % DEF_MAX_CHAR_NAME_SCORE;
}

void Game::moveNameLetterLeft() {
    playerNameHPositionCursor--;
    if (playerNameHPositionCursor < 0) {
        playerNameHPositionCursor = DEF_MAX_CHAR_NAME_SCORE - 1;
    }
}

void Game::moveNameLetterUp() {
    playerNameVPositionCursor.at(playerNameHPositionCursor)--;
    if (playerNameVPositionCursor.at(playerNameHPositionCursor) < 0) {
        playerNameVPositionCursor.at(playerNameHPositionCursor) = DEF_MAX_ALPHABET_CHARS - 1; // Go back to Z
    }
    playerName.at(playerNameHPositionCursor) = 'A' + playerNameVPositionCursor.at(playerNameHPositionCursor);
}

void Game::moveNameLetterDown() {
    playerNameVPositionCursor.at(playerNameHPositionCursor)++;
    if (playerNameVPositionCursor.at(playerNameHPositionCursor) > (DEF_MAX_ALPHABET_CHARS - 1)) {
        playerNameVPositionCursor.at(playerNameHPositionCursor) = 0; // Go back to A
    }
    // The above can be done as well by doing:
    // playerNameVPositionCursor.at(playerNameHPositionCursor) = (playerNameVPositionCursor.at(playerNameHPositionCursor) + 1) % DEF_MAX_ALPHABET_CHARS;

    playerName.at(playerNameHPositionCursor) = 'A' + playerNameVPositionCursor.at(playerNameHPositionCursor);
}