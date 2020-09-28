#include "Games1-4.MarsAttacks.h"

#include "Other.h"
#include <ctime> // To control Frames Per Second (FPS)

#include <iostream>

enum {
    FPS = 20,
};

int main(void)
{
    Game game;
    Player player;
    
    initializeCurses(true); // PDCurses

    bool quit = false;
    char input;

    clock_t last_time = clock();

    do {
        input = handleInput(game, player);
        if (input != 'q') {
            clock_t current_time = clock();
            clock_t dt = current_time - last_time;

            if (dt > CLOCKS_PER_SEC / FPS) {
                last_time = current_time;

                updateGame(game, player);
                clearScreen(); // PDCurses
                drawGame(game, player);
                refreshScreen(); // PDCurses
            }            
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
        player.move(game, false);
        break;
    case AK_RIGHT:
        player.move(game, true);
        break;
    case ' ':
        player.shootMissile();
        break;
    default:
        break;
    }
    return input;
}

void updateGame(const Game& game, Player& player) {
    player.moveMissile();
}

void drawGame(const Game& game, Player& player) {
    player.draw();
    player.getMissile().draw();
}