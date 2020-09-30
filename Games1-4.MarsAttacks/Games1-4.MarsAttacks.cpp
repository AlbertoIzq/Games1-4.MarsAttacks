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
    AlienSwarm alien_swarm;
    
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

                updateGame(game, player, shields, alien_swarm);
                clearScreen(); // PDCurses
                drawGame(game, player, shields, alien_swarm);
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

void updateGame(const Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm) {
    player.moveMissile();
    checkResolveShieldsCollision(player, shields);
    checkResolveAlienSwarmCollision(player, alien_swarm);
}

void drawGame(const Game& game, const Player& player, const std::vector<Shield>& shields, const AlienSwarm& aliens) {
    player.draw();
    player.getMissile().draw();
    drawShields(shields);
    drawAlienSwarm(aliens);
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

void drawShields(const std::vector<Shield>& shields) {
    for (const auto& s : shields) {
        s.draw();
    }
}

void drawAlienSwarm(const AlienSwarm& alien_swarm) {
    std::vector<std::vector<Alien>>::iterator it;
    for (auto& alien_row : alien_swarm.getAliens()) {
        for (auto& alien : alien_row) {
            alien.setSpriteDependingOnState();
            alien.draw();
        }
    }
}

void checkResolveShieldsCollision(Player& player, std::vector<Shield>& shields) {
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

bool isShieldCollision(const Position& projectile, const Shield& shield, Position& shield_collision_point) {
    bool is_collision{ false };
    shield_collision_point.x = DEF_NOT_IN_PLAY;
    shield_collision_point.y = DEF_NOT_IN_PLAY;

    if (projectile.x >= shield.getPosition().x && projectile.x < (shield.getPosition().x + shield.getSpriteSize().width) // Is it in line horizontally?
    && projectile.y >= shield.getPosition().y && projectile.y < (shield.getPosition().y + shield.getSpriteSize().height) // And vertically?
    && shield.getSprite().at(projectile.y - shield.getPosition().y).at(projectile.x - shield.getPosition().x) != ' ') { // Does it collide with a part of the object?
        // There is a collision
        shield_collision_point.x = projectile.x - shield.getPosition().x;
        shield_collision_point.y = projectile.y - shield.getPosition().y;
        is_collision = true;
    }
    return is_collision;
}

void resolveShieldCollision(Shield& shield, const Position& shield_collision_point) {
    std::vector<std::string> current_sprite = shield.getSprite();
    current_sprite.at(shield_collision_point.y).at(shield_collision_point.x) = ' ';
    shield.setSprite(current_sprite);
}

void checkResolveAlienSwarmCollision(Player& player, AlienSwarm& alien_swarm) {
    if (player.getMissile().getPosition().y != DEF_NOT_IN_PLAY) {
        for (auto& alien_row : alien_swarm.setAliens()) {
            for (auto& alien : alien_row) {
                if (isAlienCollision(player.getMissile().getPosition(), alien)) {
                    resolveAlienCollision(player, alien);
                    alien_swarm.setNumAliensLeft(alien_swarm.getNumAliensLeft() - 1);
                    player.resetMissile();
                    break;
                }
            }
        }
    }
}

bool isAlienCollision(const Position& projectile, const Alien& alien) {
    bool is_collision{ false };

    if (alien.getAlienState() == Alien_State::AS_ALIVE
    && projectile.x >= alien.getPosition().x && projectile.x < (alien.getPosition().x + alien.getSpriteSize().width)
    && projectile.y >= alien.getPosition().y && projectile.y < (alien.getPosition().y + alien.getSpriteSize().height)) {
        is_collision = true;
    }
    return is_collision;
}

void resolveAlienCollision(Player& player, Alien& alien) {
    alien.setAlienState(Alien_State::AS_EXPLODING);
    if (alien.getExplosionTimer() == DEF_NOT_IN_PLAY) {
        alien.setExplosionTimer(Alien::DEF_EXPLOSION_TIME);
    }


    // Incrementing player's score
    switch (alien.getAlienType()) {
    case Alien_Type::AT_10P:
        player.setScore(player.getScore() + Alien::DEF_10P_POINTS);
        break;
    case Alien_Type::AT_20P:
        player.setScore(player.getScore() + Alien::DEF_20P_POINTS);
        break;
    case Alien_Type::AT_30P:
        player.setScore(player.getScore() + Alien::DEF_30P_POINTS);
        break;
    }
}