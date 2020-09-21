#include "Games1-4.MarsAttacks.h"

#include "PDCursesUtils.h"

#include <iostream>

int main(void)
{
    Game game;
    Player player;
    
    InitializeCurses(true); // PDCurses

    bool quit = false;
    char input;

    do {
        input = handleInput(game, player);
        updateGame(game, player);
        ClearScreen(); // PDCurses
        drawGame(game, player);
        RefreshScreen(); // PDCurses
    } while (!quit);

    ShutdownCurses(); // PDCurses

    return 0;
}

char handleInput(const Game& game, Player& player) {
    return 'c';
}

void updateGame(const Game& game, Player& player) {

}

void drawGame(const Game& game, Player& player) {

}