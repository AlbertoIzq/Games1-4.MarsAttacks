#include "Games1-4.MarsAttacks.h"

#include "PDCursesUtils.h"

#include <iostream>

int main(void)
{
    Game game;
    Player player;
    
    initializeCurses(true); // PDCurses

    bool quit = false;
    char input;

    do {
        input = handleInput(game, player);
        updateGame(game, player);
        clearScreen(); // PDCurses
        drawGame(game, player);
        refreshScreen(); // PDCurses
    } while (!quit);

    shutdownCurses(); // PDCurses

    return 0;
}

char handleInput(const Game& game, Player& player) {
    return ' ';
}

void updateGame(const Game& game, Player& player) {

}

void drawGame(const Game& game, const Player& player) {
    drawSprite(player.getPosition().x, player.getPosition().y, player.getSprite(), player.getSpriteSize().height);
}