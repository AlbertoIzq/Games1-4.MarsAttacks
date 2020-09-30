#include "Games1-4.MarsAttacks.h"

#include "Other.h"
#include <ctime> // To control Frames Per Second (FPS)
#include <cmath> // For computing shields padding
#include <vector>

#include <iostream>

int main(void)
{
    Game game;
    Player player;
    std::vector<Shield> shields = iniShields(game, player);
    AlienSwarm aliens;
    
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

                updateGame(game, player, shields);
                clearScreen(); // PDCurses
                drawGame(game, player, shields, aliens);
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

void updateGame(const Game& game, Player& player, std::vector<Shield>& shields) {
    player.moveMissile();
    checkResolveShieldCollision(player, shields);
}

void drawGame(const Game& game, const Player& player, const std::vector<Shield>& shields, const AlienSwarm& aliens) {
    player.draw();
    player.getMissile().draw();
    drawShields(shields);
    drawAlienSwarm(aliens);
}

void drawShields(const std::vector<Shield>& shields) {
    for (const auto& s : shields) {
        s.draw();
    }
}

void drawAlienSwarm(const AlienSwarm& aliens) {
    std::vector<std::vector<Alien>>::iterator it;
    for (const auto& alien_row : aliens.getAliens()) {
        for (const auto& alien : alien_row) {
            alien.draw();
        }
    }
}

std::vector<Shield> iniShields(const Game& game, const Player& player) {
    std::vector<Shield> shields;

    int game_width{ game.getSize().width };
    int game_height{ game.getSize().height };
    int player_sprite_height{ player.getSpriteSize().height };
    Shield shield_properties;
    int shield_sprite_width{ shield_properties.getSpriteSize().width };
    int shield_sprite_height{ shield_properties.getSpriteSize().height };
    
    int first_padding = ceil(static_cast<float>(game_width - DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(DEF_NUM_SHIELDS + 1));
    int x_padding = floor(static_cast<float>(game_width - DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(DEF_NUM_SHIELDS + 1));

    for (size_t i{ 0 }; i < DEF_NUM_SHIELDS; i++)
    {
        Shield shield;
        shield.setPosition(first_padding + i * (shield_sprite_width + x_padding), game_height - 1 - player_sprite_height - shield_sprite_height - DEF_INI_POSITION_SHIELD_Y_OFFSET_DOWN);
        shields.push_back(shield);
    }
    return shields;
}

void checkResolveShieldCollision(Player& player, std::vector<Shield>& shields) {
    if (player.getMissile().getPosition().y != DEF_NOT_IN_PLAY) {
        Position collision_position{ DEF_NOT_IN_PLAY , DEF_NOT_IN_PLAY };
        for (auto& shield : shields) {
            if (isShieldCollision(player.getMissile().getPosition(), shield, collision_position)) {
                resolveShieldCollision(shield, collision_position);
                player.resetMissile();
                break;
            }
        }
    }
}

bool isShieldCollision(const Position& projectile, const Shield& shield, Position& collision_position) {
    bool is_collision{ false };
    collision_position.x = DEF_NOT_IN_PLAY;
    collision_position.y = DEF_NOT_IN_PLAY;

    if (projectile.x >= shield.getPosition().x && projectile.x < (shield.getPosition().x + shield.getSpriteSize().width) // Is it in line horizontally?
    && projectile.y >= shield.getPosition().y && projectile.y < (shield.getPosition().y + shield.getSpriteSize().height) // And vertically?
    && shield.getSprite().at(projectile.y - shield.getPosition().y).at(projectile.x - shield.getPosition().x) != ' ') { // Does it collide with a part of the object?
        // There is a collision
        collision_position.x = projectile.x - shield.getPosition().x;
        collision_position.y = projectile.y - shield.getPosition().y;
        is_collision = true;
    }
    return is_collision;
}

void resolveShieldCollision(Shield& shield, const Position& shield_collision_point) {
    std::vector<std::string> current_sprite = shield.getSprite();
    current_sprite.at(shield_collision_point.y).at(shield_collision_point.x) = ' ';
    shield.setSprite(current_sprite);
}