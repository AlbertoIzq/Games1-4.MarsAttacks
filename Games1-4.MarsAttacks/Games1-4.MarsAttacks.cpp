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
    AlienSwarm alien_swarm(game);
    
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
    checkResolveShieldsMissileCollision(player, shields);
    updateAlienSwarm(game, player, alien_swarm, shields);
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


void checkResolveShieldsMissileCollision(Player& player, std::vector<Shield>& shields) {
    if (player.getMissile().getPosition().y != DEF_NOT_IN_PLAY) {
        Position collision_position{ DEF_NOT_IN_PLAY , DEF_NOT_IN_PLAY };
        for (auto& shield : shields) {
            if (isShieldMissileCollision(player.getMissile().getPosition(), shield, collision_position)) {
                resolveShieldCollision(shield, collision_position);
                player.setMissile().reset();
                break;
            }
        }
    }
}

bool isShieldMissileCollision(const Position& projectile, const Shield& shield, Position& shield_collision_point) {
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


void updateAlienSwarm(const Game& game, Player& player, AlienSwarm& alien_swarm, std::vector<Shield>& shields) {
    checkResolveAlienSwarmMissileCollision(player, alien_swarm);
    updateAlienSwarmExplosions(alien_swarm);
    updateAlienSwarmMovementAndShieldCollision(game, alien_swarm, shields);
}

void checkResolveAlienSwarmMissileCollision(Player& player, AlienSwarm& alien_swarm) {
    if (player.getMissile().getPosition().y != DEF_NOT_IN_PLAY) {
        for (auto& alien_row : alien_swarm.setAliens()) {
            for (auto& alien : alien_row) {
                if (isAlienMissileCollision(player.getMissile().getPosition(), alien)) {
                    resolveAlienMissileCollision(player, alien);
                    alien_swarm.setNumAliensLeft(alien_swarm.getNumAliensLeft() - 1);
                    player.setMissile().reset();
                    break;
                }
            }
        }
    }
}

bool isAlienMissileCollision(const Position& projectile, const Alien& alien) {
    bool is_collision{ false };

    if (alien.getAlienState() == Alien_State::AS_ALIVE
    && projectile.x >= alien.getPosition().x && projectile.x < (alien.getPosition().x + alien.getSpriteSize().width)
    && projectile.y >= alien.getPosition().y && projectile.y < (alien.getPosition().y + alien.getSpriteSize().height)) {
        is_collision = true;
    }
    return is_collision;
}

void resolveAlienMissileCollision(Player& player, Alien& alien) {
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

void updateAlienSwarmExplosions(AlienSwarm& alien_swarm) {
    for (auto& alien_row : alien_swarm.setAliens()) {
        for (auto& alien : alien_row) {
            alien.updateExplosion();
        }
    }
}

void updateAlienSwarmMovementAndShieldCollision(const Game& game, AlienSwarm& alien_swarm, std::vector<Shield>& shields) {
    alien_swarm.setMovementTimer(alien_swarm.getMovementTimer() - 1);

    bool move_horizontal = 0 >= alien_swarm.getMovementTimer();

    Alien alien_left;
    Alien alien_right;
    Alien alien_bottom;

    alien_swarm.getAlienLeftRightBottom(alien_left, alien_right, alien_bottom);

    // Move downwards
    if (((alien_right.getPosition().x + alien_right.getSpriteSize().width) >= game.getSize().width && alien_swarm.getDirectionRight()) ||
        (alien_left.getPosition().x <= 0 && !alien_swarm.getDirectionRight()) && move_horizontal && alien_swarm.getLine() > 0) {
        move_horizontal = false;
        alien_swarm.setPositionDiff(0, 1);
        alien_swarm.setLine(alien_swarm.getLine() - 1);
        alien_swarm.setDirectionRight(!alien_swarm.getDirectionRight());
        alien_swarm.resetMovementTimer();
        checkResolveAlienSwarmShieldsCollision(alien_swarm, shields);
    }

    if (move_horizontal) {
        if (alien_swarm.getDirectionRight()) {
            alien_swarm.setPositionDiff(1, 0);
        }
        else {
            alien_swarm.setPositionDiff(-1, 0);
        }
        alien_swarm.resetMovementTimer();
        checkResolveAlienSwarmShieldsCollision(alien_swarm, shields);
    }
}

void checkResolveAlienSwarmShieldsCollision(const AlienSwarm& alien_swarm, std::vector<Shield>& shields) {
    for (auto& alien_row : alien_swarm.getAliens()) {
        for (auto& alien : alien_row) {
            if (alien.getAlienState() == Alien_State::AS_ALIVE) {
                collideShieldsWithAlien(shields, alien);
            }
        }
    }
}

void collideShieldsWithAlien(std::vector<Shield>& shields, Alien& alien) {
    for (auto& shield : shields) {
        if (alien.getPosition().x < (shield.getPosition().x + shield.getSpriteSize().width) && (alien.getPosition().x + alien.getSpriteSize().width) >= shield.getPosition().x
            && alien.getPosition().y < (shield.getPosition().y + shield.getSpriteSize().height) && (alien.getPosition().y + alien.getSpriteSize().height) >= shield.getPosition().y) 
        {
            // Alien and shield are colliding
            int dy = alien.getPosition().y - shield.getPosition().y;
            int dx = alien.getPosition().x - shield.getPosition().x;

            for (int h{ 0 }; h < alien.getSpriteSize().height; h++) {
                int shield_dy = dy + h;
                if (shield_dy >= 0 && shield_dy < shield.getSpriteSize().height) {
                    for (int w{ 0 }; w < alien.getSpriteSize().width; w++) {
                        int shield_dx = dx + w;
                        if (shield_dx >= 0 && shield_dx < shield.getSpriteSize().width) {
                            Position position_collision{ shield_dx, shield_dy };
                            resolveShieldCollision(shield, position_collision);
                        }
                    }
                }
            }
            break;
        }
    }
}