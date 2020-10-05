#include "Games1-4.MarsAttacks.h"

#include "Other.h"
#include <ctime> // To control Frames Per Second (FPS)
#include <cmath> // For computing shields padding
#include <vector>

int main(void)
{
    srand(time(NULL));

    Game game;
    Player player;
    std::vector<Shield> shields = iniShields(game, player);
    AlienSwarm alien_swarm(game);
    AlienUFO ufo;

    initializeCurses(true); // PDCurses

    bool quit = false;
    char input;

    clock_t last_time = clock();

    do {
        input = handleInput(game, player, shields, alien_swarm, ufo);
        if (input != 'q') {
            clock_t current_time = clock();
            clock_t dt = current_time - last_time;

            if (dt > CLOCKS_PER_SEC / DEF_FPS) {
                last_time = current_time;

                updateGame(game, player, shields, alien_swarm, ufo);
                clearScreen(); // PDCurses
                drawGame(game, player, shields, alien_swarm, ufo);
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


std::vector<Shield> iniShields(const Game& game, const Player& player) {
    std::vector<Shield> shields;

    int game_width{ game.getWindowSize().width };
    int game_height{ game.getWindowSize().height };
    int player_sprite_height{ player.getSpriteSize().height };
    Shield shield_properties;
    int shield_sprite_width{ shield_properties.getSpriteSize().width };
    int shield_sprite_height{ shield_properties.getSpriteSize().height };

    int first_padding = ceil(static_cast<float>(game_width - Shield::DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(Shield::DEF_NUM_SHIELDS + 1));
    int x_padding = floor(static_cast<float>(game_width - Shield::DEF_NUM_SHIELDS * shield_sprite_width) / static_cast<float>(Shield::DEF_NUM_SHIELDS + 1));

    for (size_t i{ 0 }; i < Shield::DEF_NUM_SHIELDS; i++)
    {
        Shield shield;
        shield.setPosition(first_padding + i * (shield_sprite_width + x_padding), game_height - 1 - player_sprite_height - shield_sprite_height - Shield::DEF_POSITION_Y_OFFSET_DOWN_PLAYER);
        shields.push_back(shield);
    }
    return shields;
}


int handleInput(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo) {
    int input = getChar();
    switch (input)
    {
    case 'q':
        return input;
    case 'i':
        if (game.getCurrentState() == Game_State::GS_INTRO) {
            game.setCurrentState(Game_State::GS_INSTRUCTIONS_1);
        }
        else if (game.getCurrentState() == Game_State::GS_INSTRUCTIONS_1) {
            game.setCurrentState(Game_State::GS_INSTRUCTIONS_2);
        }
        break;
    case AK_LEFT:
        if (game.getCurrentState() == Game_State::GS_PLAY) {
            player.move(game, false);
        }
        break;
    case AK_RIGHT:
        if (game.getCurrentState() == Game_State::GS_PLAY) {
            player.move(game, true);
        }
        break;
    case ' ':
        if (game.getCurrentState() == Game_State::GS_INTRO ||
        game.getCurrentState() == Game_State::GS_INSTRUCTIONS_1 ||
        game.getCurrentState() == Game_State::GS_INSTRUCTIONS_2) {
            game.setCurrentState(Game_State::GS_PLAY);
        }
        else if (game.getCurrentState() == Game_State::GS_PLAY) {
            player.shootMissile();
        }
        else if (game.getCurrentState() == Game_State::GS_PLAYER_DEAD) {
            if (player.getLives() <= 0) {
                game.setCurrentState(Game_State::GS_GAME_OVER);
            } else {
                game.setCurrentState(Game_State::GS_WAIT);
                game.setWaitTimer(Game::DEF_WAIT_TIMER);
            }
        }
        else if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
            game.setCurrentState(Game_State::GS_INTRO);
            resetGame(game, player, shields, alien_swarm, ufo);
        }
        break;
    default:
        break;
    }
    return input;
}

void updateGame(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo) {
    if (game.getCurrentState() == Game_State::GS_PLAY) {
        updateMissile(player, shields);
        updateAlienSwarm(game, player, alien_swarm, shields);
        updateUFO(game, player, ufo);
        // If player is shot
        if (player.getIsShot()) {
            game.setCurrentState(Game_State::GS_PLAYER_DEAD);
            player.setIsShot(false);
        }
        // When all aliens are killed, we go to next level
        if (alien_swarm.getNumAliensLeft() <= 0) {
            game.setLevel((game.getLevel() % Game::DEF_LEVEL_MAX) + 1);
            game.setCurrentState(Game_State::GS_WAIT);
            resetLevel(game, player, shields, alien_swarm, ufo);
        }
    } else if (game.getCurrentState() == Game_State::GS_WAIT) {
        game.setWaitTimer(game.getWaitTimer() - 1);
        player.changeDeadSprite(); // Only if it's dead
        if (game.getWaitTimer() <= 0) {
            game.setCurrentState(Game_State::GS_PLAY);
            player.setSprite(Player::DEF_SPRITE);
        }
    }
}

void drawGame(const Game& game, const Player& player, const std::vector<Shield>& shields, const AlienSwarm& alien_swarm, const AlienUFO& ufo) {
    if (game.getCurrentState() == Game_State::GS_INTRO) {
        drawIntroScreen(game);
    }
    else if (game.getCurrentState() == Game_State::GS_INSTRUCTIONS_1) {
        drawInstructionsScreen1(game);
    }
    else if (game.getCurrentState() == Game_State::GS_INSTRUCTIONS_2) {
        drawInstructionsScreen2(game);
    }
    else if (game.getCurrentState() == Game_State::GS_PLAY || game.getCurrentState() == Game_State::GS_PLAYER_DEAD
    || game.getCurrentState() == Game_State::GS_WAIT) {
        drawGameStats(game, player);
        player.draw();
        player.getMissile().draw();
        drawShields(shields);
        drawAlienSwarm(alien_swarm);
        drawBombs(alien_swarm);
        ufo.draw();
    }
    else if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        drawGameOverScreen(game);
    }
}


void updateMissile(Player& player, std::vector<Shield>& shields) {
    checkResolveShieldsMissileCollision(player, shields);
    player.moveMissile();
}

void updateAlienSwarm(Game& game, Player& player, AlienSwarm& alien_swarm, std::vector<Shield>& shields) {
    checkResolveAlienSwarmMissileCollision(player, alien_swarm);
    updateAlienSwarmExplosions(alien_swarm);
    updateAlienSwarmMovementShieldCollisionAndShooting(game, alien_swarm, shields);
    updateAlienSwarmBombs(game, alien_swarm, shields, player);
}

void updateUFO(const Game& game, Player& player, AlienUFO& ufo) {
    ufo.putInPlay();
    checkResolveUFOMissileCollision(player, ufo);
    ufo.updateExplosion();
    ufo.move(game);
}


void drawIntroScreen(const Game& game) {
    std::vector<std::string> header{ "Release date: 05/10/2020" ,
                                     "Author: Alberto Izquierdo aka Albertroll",
                                     "Copyright-All rights reserved" };
    std::string line_1{ "Welcome to this stupid Text Invaders game!" };
    std::string line_2{ "Press I key to go to instructions or Space bar to start" };
    std::string line_bottom{ "Side note: Feel free to put some good arcade music on =)" };

    const int y_pos = game.getWindowSize().height / 2;
    const int y_pos_bottom = game.getWindowSize().height - 1;
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;

    drawSprite(0, 0, header);
    drawString(x_pos_1, y_pos, line_1);
    drawString(x_pos_2, y_pos + 2, line_2);
    drawString(0, y_pos_bottom, line_bottom);
}

void drawInstructionsScreen1(const Game& game) {
    std::string line_1{ "INSTRUCTIONS" };
    std::string line_2{ "Who the hell wastes time reading the instructions" };
    std::string line_3{ "when those bastards are awaiting to invade the Earth?" };
    std::string line_bottom_1{ "Side note: Just kidding! Press I key to read the instructions" };
    std::string line_bottom_2{ "           or press Space bar to start" };

    const int y_pos = game.getWindowSize().height / 2;
    const int y_pos_bottom = game.getWindowSize().height - 2;
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;
    const int x_pos_3 = (game.getWindowSize().width - line_3.size()) / 2;

    drawString(x_pos_1, y_pos, line_1);
    drawString(x_pos_2, y_pos + 1, line_2);
    drawString(x_pos_3, y_pos + 2, line_3);

    drawString(0, y_pos_bottom, line_bottom_1);
    drawString(0, y_pos_bottom + 1, line_bottom_2);
}

void drawInstructionsScreen2(const Game& game) {
    std::string line_1{ "INSTRUCTIONS" };
    std::string line_2{ "Bla, bla, bla, bla, bla" };

    const int y_pos = game.getWindowSize().height / 2;
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;

    drawString(x_pos_1, y_pos, line_1);
    drawString(x_pos_2, y_pos + 1, line_2);
}

void drawGameOverScreen(const Game& game) {
    std::string line_1{ "GAME OVER" };
    std::string line_2{ "Some damned invaders have just killed you and conquered Earth!" };

    std::string line_3{ "You have 2 options:" };
    std::string line_4{ "- Press Q key to exit the game and go cry somewhere else" };
    std::string line_5{ "- Press Space bar and take revenge by killing all those bastards!!" };

    const int y_pos = game.getWindowSize().height / 2;
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;

    drawString(x_pos_1, y_pos, line_1);
    drawString(x_pos_2, y_pos + 2, line_2);
    drawString(x_pos_2, y_pos + 4, line_3);
    drawString(x_pos_2, y_pos + 5, line_4);
    drawString(x_pos_2, y_pos + 6, line_5);
}


void resetLevel(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo) {
    game.resetLevel();
    player.resetLevel();
    resetShields(game, player, shields);
    alien_swarm.reset(game);
    ufo.reset();
}

void resetGame(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo) {
    game.resetAll();
    player.resetAll();
    resetShields(game, player, shields);
    alien_swarm.reset(game);
    ufo.reset();
}

void resetShields(const Game& game, const Player& player, std::vector<Shield>& shields) {
    shields.clear();
    shields = iniShields(game, player);
}


void checkResolveShieldsMissileCollision(Player& player, std::vector<Shield>& shields) {
    if (player.getMissile().getPosition().y != DEF_NOT_IN_PLAY) {
        Position collision_position{ DEF_NOT_IN_PLAY , DEF_NOT_IN_PLAY };
        for (auto& shield : shields) {
            if (isShieldCollision(player.getMissile().getPosition(), shield, collision_position)) {
                resolveShieldCollision(shield, collision_position);
                player.setMissile().reset();
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
    current_sprite.at(shield_collision_point.y).at(shield_collision_point.x) = ' '; // Shield is destroyed where is hit
    shield.setSprite(current_sprite);
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


void updateAlienSwarmMovementShieldCollisionAndShooting(Game& game, AlienSwarm& alien_swarm, std::vector<Shield>& shields) {
    alien_swarm.setMovementTimer(alien_swarm.getMovementTimer() - 1);

    bool move_horizontal = 0 >= alien_swarm.getMovementTimer();

    Alien alien_left;
    Alien alien_right;
    Alien alien_bottom; // Useless

    alien_swarm.getAlienLeftRightBottom(alien_left, alien_right, alien_bottom);

    // Move downwards
    if (((alien_right.getPosition().x + alien_right.getSpriteSize().width) >= game.getWindowSize().width && alien_swarm.getDirectionRight()) ||
        (alien_left.getPosition().x <= 0 && !alien_swarm.getDirectionRight()) && move_horizontal && alien_swarm.getLine() > 0) {
        move_horizontal = false;
        alien_swarm.movePositionDiff(0, 1);
        alien_swarm.setLine(alien_swarm.getLine() - 1);
        alien_swarm.setDirectionRight(!alien_swarm.getDirectionRight());
        alien_swarm.resetMovementTimer();
        checkResolveAlienSwarmShieldsCollision(alien_swarm, shields);

        if (alien_swarm.getLine() <= 0) {
            game.setCurrentState(Game_State::GS_GAME_OVER);
        }
    }

    // Move horizontally
    if (move_horizontal) {
        if (alien_swarm.getDirectionRight()) {
            alien_swarm.movePositionDiff(1, 0);
        }
        else {
            alien_swarm.movePositionDiff(-1, 0);
        }
        alien_swarm.resetMovementTimer();
        checkResolveAlienSwarmShieldsCollision(alien_swarm, shields);
    }

    // Shoot bomb
    if (alien_swarm.shouldShootBomb()) {
        int numShoots = ((rand() % 3) + 1) - alien_swarm.getNumBombsInPlay();
        for (int i{ 0 }; i < numShoots; i++) {
            Alien alien;
            if (alien_swarm.getAlienToShootBomb(alien)) {
                alien_swarm.shootBomb(alien);
            }
            else {
                break; // No aliens available to shoot
            }
        }
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


void updateAlienSwarmBombs(const Game& game, AlienSwarm& alien_swarm, std::vector<Shield>& shields, Player& player) {
    alien_swarm.moveChangeAnimationBombs(game);
    for (auto& bomb : alien_swarm.setBombs()) {
        checkResolveShieldsBombCollision(alien_swarm, bomb, shields);
        checkResolvePlayerBombCollision(alien_swarm, bomb, player);
    }
}

void checkResolvePlayerBombCollision(AlienSwarm& alien_swarm, AlienBomb& bomb, Player& player) {
    if (isCollision(bomb.getPosition(), player.getPosition(), player.getSpriteSize())) {
        player.gotShot();
        bomb.reset();
        alien_swarm.setNumBombsInPlay(alien_swarm.getNumBombsInPlay() - 1);
    }
}

bool isCollision(const Position& projectile, const Position& object_position, const Size& object_size) {
    bool is_collision{ false };

    if (projectile.x >= object_position.x && projectile.x < (object_position.x + object_size.width) // Is it in line horizontally?
    && projectile.y >= object_position.y && projectile.y < (object_position.y + object_size.height)) { // And vertically?
        // There is a collision
        is_collision = true;
    }
    return is_collision;
}

void checkResolveShieldsBombCollision(AlienSwarm& alien_swarm, AlienBomb& bomb, std::vector<Shield>& shields) {
    if (bomb.getPosition().y != DEF_NOT_IN_PLAY) {
        Position collision_position{ DEF_NOT_IN_PLAY , DEF_NOT_IN_PLAY };
        for (auto& shield : shields) {
            if (isShieldCollision(bomb.getPosition(), shield, collision_position)) {
                resolveShieldCollision(shield, collision_position);
                bomb.reset();
                alien_swarm.setNumBombsInPlay(alien_swarm.getNumBombsInPlay() - 1);
                break;
            }
        }
    }
}


void checkResolveUFOMissileCollision(Player& player, AlienUFO& ufo) {
    if (isCollision(player.getMissile().getPosition(), ufo.getPosition(), ufo.getSpriteSize())) {
        player.setScore(player.getScore() + ufo.getPoints());
        player.setMissile().reset();
        ufo.setExploding(true);
        ufo.setSprite(AlienUFO::DEF_SPRITE_EXPLOSION);
        if (ufo.getExplosionTimer() == DEF_NOT_IN_PLAY) {
            ufo.setExplosionTimer(AlienUFO::DEF_EXPLOSION_TIME);
        }
    }
}


void drawShields(const std::vector<Shield>& shields) {
    for (const auto& shield : shields) {
        shield.draw();
    }
}

void drawAlienSwarm(const AlienSwarm& alien_swarm) {
    for (auto& alien_row : alien_swarm.getAliens()) {
        for (auto& alien : alien_row) {
            alien.setSpriteDependingOnState();
            alien.draw();
        }
    }
}

void drawBombs(const AlienSwarm& alien_swarm) {
    for (auto& bomb : alien_swarm.getBombs()) {
        bomb.draw();
    }
}

void drawGameStats(const Game& game, const Player& player) {
    std::string line_score{ "Score: " };
    std::string line_level{ "LEVEL " };
    std::string line_lives{ "Lives: " };

    line_score += std::to_string(player.getScore());
    line_level += std::to_string(game.getLevel());
    line_lives += std::to_string(player.getLives());

    const int x_pos_score = 0;
    const int x_pos_level = (game.getWindowSize().width - line_level.size()) / 2;
    const int x_pos_lives = game.getWindowSize().width - line_lives.size();

    drawString(x_pos_score, 0, line_score);
    drawString(x_pos_level, 0, line_level);
    drawString(x_pos_lives, 0, line_lives);
}