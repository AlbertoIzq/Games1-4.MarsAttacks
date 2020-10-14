#include "Games1-4.MarsAttacks.h"

#include "Other.h"
#include <ctime> // To control Frames Per Second (FPS)
#include <cmath> // For computing shields padding
#include <vector>
#include <algorithm> // To sort high scores table
#include <fstream> // For file I/O
#include <iostream>

int main(void)
{
    srand(static_cast<unsigned>(time(NULL)));
    const std::string DEF_FILE_NAME{ "TextInvaders-HighScores.txt" };

    initializeCurses(true); // PDCurses, before game object to be able to resize screen

    Game game;
    Player player;
    std::vector<Shield> shields = iniShields(game, player);
    AlienSwarm alien_swarm(game);
    AlienUFO ufo;
    std::vector<Score> high_score_table;

    loadHighScores(high_score_table, DEF_FILE_NAME);

    bool quit = false;
    char input;

    clock_t last_time = clock();

    do {
        input = handleInput(game, player, shields, alien_swarm, ufo, high_score_table, DEF_FILE_NAME);
        if (input != 'e') {
            clock_t current_time = clock();
            clock_t dt = current_time - last_time;

            if (dt > CLOCKS_PER_SEC / DEF_FPS) {
                last_time = current_time;

                updateGame(game, player, shields, alien_swarm, ufo);
                clearScreen(); // PDCurses
                drawGame(game, player, shields, alien_swarm, ufo, high_score_table);
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


int handleInput(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo, std::vector<Score>& high_score_table, const std::string& file_name) {
    int input = getChar();
    switch (input)
    {
    case 'e':
        return input;
    case 'i':
        handleInputI(game);
        break;
    case AK_LEFT:
        handleInputLeft(game, player);
        break;
    case AK_RIGHT:
        handleInputRight(game, player);
        break;
    case AK_UP:
        handleInputUp(game);
        break;
    case AK_DOWN:
        handleInputDown(game);
        break;
    case ' ':
        handleInputSpace(game, player, shields, alien_swarm, ufo, high_score_table, file_name);
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

void drawGame(const Game& game, const Player& player, const std::vector<Shield>& shields, const AlienSwarm& alien_swarm, const AlienUFO& ufo, const std::vector<Score>& high_score_table) {
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
    else if (game.getCurrentState() == Game_State::GS_HIGH_SCORES) {
        drawHighScoresScreen(game, high_score_table);
    }
}


void handleInputI(Game& game) {
    if (game.getCurrentState() == Game_State::GS_INTRO) {
        game.setCurrentState(Game_State::GS_INSTRUCTIONS_1);
    }
    else if (game.getCurrentState() == Game_State::GS_INSTRUCTIONS_1) {
        game.setCurrentState(Game_State::GS_INSTRUCTIONS_2);
    }
}

void handleInputLeft(Game& game, Player& player) {
    if (game.getCurrentState() == Game_State::GS_PLAY) {
        player.move(game, false);
    }
    else if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        game.moveNameLetterLeft();
    }
}

void handleInputRight(Game& game, Player& player) {
    if (game.getCurrentState() == Game_State::GS_PLAY) {
        player.move(game, true);
    }
    else if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        game.moveNameLetterRight();
    }
}

void handleInputUp(Game& game) {
    if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        game.moveNameLetterUp();
    }
}

void handleInputDown(Game& game) {
    if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        game.moveNameLetterDown();
    }
}

void handleInputSpace(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo, std::vector<Score>& high_score_table, const std::string& file_name) {
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
        }
        else {
            game.setCurrentState(Game_State::GS_WAIT);
            game.setWaitTimer(Game::DEF_WAIT_TIMER);
        }
    }
    else if (game.getCurrentState() == Game_State::GS_GAME_OVER) {
        addScore(high_score_table, game.getPlayerName(), player.getScore(), file_name);
        game.setCurrentState(Game_State::GS_HIGH_SCORES);
    }
    else if (game.getCurrentState() == Game_State::GS_HIGH_SCORES) {
        resetGame(game, player, shields, alien_swarm, ufo);
        game.setCurrentState(Game_State::GS_INTRO);
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
    std::vector<std::string> header{ "Release date: 14/10/2020 v1.0" ,
                                     "Author: Alberto Izquierdo aka Albertroll",
                                     "Copyright-All lefts reserved" };
    drawSprite(0, 0, header);

    std::string line_1{ "Welcome to this stupid TEXT INVADERS game!" };
    std::string line_2{ "Press I key to go to instructions or Space bar to start" };

    const int y_pos = game.getWindowSize().height / 2;
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;

    drawString(x_pos_1, y_pos, line_1);
    drawString(x_pos_2, y_pos + 2, line_2);
    
    std::string line_bottom{ "Side note: Feel free to put some good arcade music on =)" };
    const int y_pos_bottom = game.getWindowSize().height - 1;
    drawString(0, y_pos_bottom, line_bottom);
}

void drawInstructionsScreen1(const Game& game) {
    std::string line_header{ "INSTRUCTIONS" };
    const int x_pos_header = (game.getWindowSize().width - line_header.size()) / 2;
    drawString(x_pos_header, 2, line_header);

    std::string line_1{ "Who the hell wastes time reading the instructions" };
    std::string line_2{ "when those bastards are awaiting to invade the Earth?" };
    
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    const int x_pos_2 = (game.getWindowSize().width - line_2.size()) / 2;

    drawString(x_pos_1, 4, line_1);
    drawString(x_pos_2, 5, line_2);

    std::string line_3{ "Stop wasting time and press Space bar to start the bloodbath" };
    const int x_pos_3 = (game.getWindowSize().width - line_3.size()) / 2;
    drawString(x_pos_3, 7, line_3);

    std::string line_bottom_1{ "Side note: Just kidding! Press I key to read the damned instructions" };
    const int y_pos_bottom = game.getWindowSize().height - 1;
    drawString(0, y_pos_bottom, line_bottom_1);
}

void drawInstructionsScreen2(const Game& game) {
    std::string line_header_1{ "INSTRUCTIONS" };
    const int x_pos_header_1 = (game.getWindowSize().width - line_header_1.size()) / 2;
    drawString(x_pos_header_1, 2, line_header_1);

    std::vector<string> instructions_1{
        {"- The aim of the game is to shoot the invaders with your missile while "},
        {"avoiding their shots and preventing an invasion. "},
        {"- Amassing a high score is a further objective and one that must be "},
        {"prioritised against your continued survival."},
        {"- There is no time limit, except for the fact that if you do not shoot "},
        {"them all before they reach the bottom of the screen the game ends."}
    };

    const int y_pos_1 = 4;
    const int x_pos = 1;

    for (unsigned i{ 0 }; i < instructions_1.size(); i++) {
        drawString(x_pos, y_pos_1 + i, instructions_1.at(i));
    }

    std::string line_header_2{ "CONTROLS" };
    const int y_pos_header_2 = y_pos_1 + instructions_1.size() + 1;
    const int x_pos_header_2 = (game.getWindowSize().width - line_header_2.size()) / 2;
    drawString(x_pos_header_2, y_pos_header_2, line_header_2);
    
    std::vector<string> instructions_2{
        {"- Space bar => To shoot those bastards and resume the game after being hit"},
        {"- Left arrow key => Move to the left"},
        {"- Right arrow key => Move to the right"},
        {"- E key => Exit the game"}
    };
    
    const int y_pos_2 = y_pos_header_2 + 2;

    for (unsigned i{ 0 }; i < instructions_2.size(); i++) {
        drawString(x_pos, y_pos_2 + i, instructions_2.at(i));
    }
    
    std::string line_bottom{ "Stop wasting time and press Space bar to start the bloodbath" };
    const int x_pos_bottom = (game.getWindowSize().width - line_bottom.size()) / 2;
    const int y_pos_bottom = y_pos_2 + instructions_2.size() + 4;
    drawString(x_pos_bottom, y_pos_bottom, line_bottom);
}

void drawGameOverScreen(const Game& game) {
    std::string line_game_over_1{ "GAME OVER" };
    std::string line_game_over_2{ "Some damned invaders have just killed you and conquered Earth" };

    const int y_pos_game_over_1 = game.getWindowSize().height * 1 / 4;
    const int x_pos_game_over_1 = (game.getWindowSize().width - line_game_over_1.size()) / 2;
    const int x_pos_game_over_2 = (game.getWindowSize().width - line_game_over_2.size()) / 2;

    drawString(x_pos_game_over_1, y_pos_game_over_1, line_game_over_1);
    drawString(x_pos_game_over_2, y_pos_game_over_1 + 2, line_game_over_2);

    std::string line_name_1{ "Please enter your shitty name:" };

    const int y_pos_name_1 = game.getWindowSize().height / 2;
    const int x_pos_name_1 = (game.getWindowSize().width - line_name_1.size()) / 2;
    const int x_pos_name_2 = (game.getWindowSize().width - Score::DEF_MAX_CHAR_NAME_SCORE) / 2;

    drawString(x_pos_name_1, y_pos_name_1, line_name_1);
    game.drawPlayerName(x_pos_name_2, y_pos_name_1 + 1);

    std::string line_1{ "Press Space bar to check how well you scored among previous fuckers" };
    const int x_pos_line_1 = (game.getWindowSize().width - line_1.size()) / 2;
    drawString(x_pos_line_1, y_pos_name_1 + 3, line_1);
}

void drawHighScoresScreen(const Game& game, const std::vector<Score>& high_score_table) {
    std::string line_1{ "HIGH SCORES" };
    const int x_pos_1 = (game.getWindowSize().width - line_1.size()) / 2;
    drawString(x_pos_1, 2, line_1);

    int y_pos_end_table{ 0 };
    drawHighScoreTable(game, high_score_table, 4, y_pos_end_table);

    std::string line_op_1{ "You have 2 options:" };
    std::string line_op_2{ "- Press E key to exit the game and go cry somewhere else" };
    std::string line_op_3{ "- Press Space bar to take revenge by killing all those bastards!!" };

    const int y_pos_op_1 = y_pos_end_table + 3;
    const int x_pos_op_1 = (game.getWindowSize().width - line_op_3.size()) / 2;

    drawString(x_pos_op_1, y_pos_op_1, line_op_1);
    drawString(x_pos_op_1, y_pos_op_1 + 1, line_op_2);
    drawString(x_pos_op_1, y_pos_op_1 + 2, line_op_3);
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

void drawHighScoreTable(const Game& game, const std::vector<Score>& high_score_table, const int& y_pos, int& y_pos_end) {
    const int y_padding{ 2 };
    const int x_padding{ 20 };
    const int score_max_digits{ 4 };
    const int x_pos_name = (game.getWindowSize().width - Score::DEF_MAX_CHAR_NAME_SCORE - score_max_digits - x_padding) / 2;

    for (unsigned i{ 0 }; i < high_score_table.size() && i < DEF_MAX_SCORES; i++) {
        std::string name = high_score_table.at(i).getName();
        drawString(x_pos_name, y_pos + y_padding * i, name);

        std::string score = std::to_string(high_score_table.at(i).getScore());
        const int x_pos_score = x_pos_name + name.size() + x_padding - score.size();
        drawString(x_pos_score, y_pos + y_padding * i, score);
    }

    y_pos_end = y_pos + y_padding * high_score_table.size();
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


void addScore(std::vector<Score>& high_score_table, const std::string& name, const int& score, const std::string& file_name) {
    Score high_score;
    high_score.setName(name);
    high_score.setScore(score);

    high_score_table.push_back(high_score);
    std::sort(high_score_table.begin(), high_score_table.end(), scoreCompare); // Descending order

    saveHighScores(high_score_table, file_name);
}

bool scoreCompare(const Score& score_1, const Score& score_2) {
    return score_1.getScore() > score_2.getScore();
}


void saveHighScores(const std::vector<Score>& high_score_table, const std::string& file_name) {
    std::ofstream out_file;
    out_file.open(file_name);

    if (out_file.is_open()) {
        for (unsigned i{ 0 }; i < high_score_table.size() && i < DEF_MAX_SCORES; i++) {
            out_file << high_score_table.at(i).getName() << " " << high_score_table.at(i).getScore() << std::endl;
        }
        out_file.close();
    }
    
    /*BINARY FILE - NOT WORKING
    
    std::ofstream out_file;
    out_file.open(DEF_FILE_NAME, std::fstream::binary);

    Score score_array[DEF_MAX_SCORES];

    for (int i = 0; i < DEF_MAX_SCORES; i++) {
        if (i < high_score_table.size()) {
            score_array[i].setName(high_score_table.at(i).getName());
            score_array[i].setScore(high_score_table.at(i).getScore());
        }
        else {
            Score score;
            score_array[i] = score;
        }
    }

    for (int i{ 0 }; i < DEF_MAX_SCORES; i++)
        out_file.write((char*)&score_array[i], sizeof(Score));

    out_file.close();*/
}

void loadHighScores(std::vector<Score>& high_score_table, const std::string& file_name) {
    std::ifstream in_file;
    in_file.open(file_name);

    Score score;
    std::string name;
    int score_val;


    if (in_file.is_open()) {
        while (!in_file.eof()) {
            in_file >> std::ws;
            if (in_file.eof()) {
                break;
            }
            in_file >> name >> score_val;
            score.setName(name);
            score.setScore(score_val);

            high_score_table.push_back(score);
        }
        in_file.close();
    }

    /*BINARY FILE - NOT WORKING

    std::ifstream in_file;
    in_file.open(DEF_FILE_NAME, std::fstream::binary);

    Score score_array[DEF_MAX_SCORES];

    for (int i = 0; i < 3; i++)
        in_file.read((char*)&score_array[i], sizeof(Score));
    in_file.close();

    for (int i = 0; i < DEF_MAX_SCORES; i++) {
        high_score_table.at(i).setName(score_array[i].getName());
        high_score_table.at(i).setScore(score_array[i].getScore());
    }*/
}