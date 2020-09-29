#include "Games1-4.MarsAttacks.h"

#include "Other.h"
#include <ctime> // To control Frames Per Second (FPS)
#include <cmath> // For computing shields padding
#include <array>

#include <iostream>

int main(void)
{
    Game game;
    Player player;
    std::array<Shield, DEF_NUM_SHIELDS> shields;
    iniShields(game, player, shields);
    
    initializeCurses(true); // PDCurses

    bool quit = false;
    char input;

    clock_t last_time = clock();

    do {
        input = handleInput(game, player);
        if (input != 'q') {
            clock_t current_time = clock();
            clock_t dt = current_time - last_time;

            if (dt > CLOCKS_PER_SEC / DEF_FPS) {
                last_time = current_time;

                updateGame(game, player);
                clearScreen(); // PDCurses
                drawGame(game, player, shields);
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

void drawGame(const Game& game, const Player& player, const std::array<Shield, DEF_NUM_SHIELDS>& shields) {
    player.draw();
    player.getMissile().draw();
    drawShields(shields);
}

void drawShields(const std::array<Shield, DEF_NUM_SHIELDS>& shields) {
    for (auto s : shields) {
        s.draw();
    }
}

void iniShields(const Game& game, const Player& player, std::array<Shield, DEF_NUM_SHIELDS>& shields) {

    int game_width{ game.getSize().width };
    int game_height{ game.getSize().height };
    int player_sprite_height{ player.getSpriteSize().height };
    int shield_sprite_width{ shields.at(0).getSpriteSize().width };
    int shield_sprite_height{ shields.at(0).getSpriteSize().height };
    

    int first_padding = ceil(static_cast<float>(game_width - DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(DEF_NUM_SHIELDS + 1));
    int x_padding = floor(static_cast<float>(game_width - DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(DEF_NUM_SHIELDS + 1));

    for (size_t i{ 0 }; i < shields.size(); i++)
    {
        shields.at(i).setPosition(first_padding + i * (shield_sprite_width + x_padding), game_height - 1 - player_sprite_height - shield_sprite_height - DEF_INI_POSITION_SHIELD_Y_OFFSET_DOWN);
    }
}