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
        if (input != 'q') {
            updateGame(game, player);
            clearScreen(); // PDCurses
            drawGame(game, player);
            refreshScreen(); // PDCurses
        }
        else {  
            quit = true;
        }
        
    } while (!quit);

    shutdownCurses(); // PDCurses

    return 0;
}

int handleInput(const Game& game, Player& player) {
    int input = getChar();
    switch (input)
    {
    case 'q':
        return input;
    case AK_LEFT:
        player.movePlayer(game, false);
        break;
    case AK_RIGHT:
        player.movePlayer(game, true);
        break;
    default:
        break;
    }
    
    return 1;
}

void updateGame(const Game& game, Player& player) {

}

void drawGame(const Game& game, const Player& player) {
    drawSprite(player.getPosition().x, player.getPosition().y, player.getSprite(), player.getSpriteSize().height);
}