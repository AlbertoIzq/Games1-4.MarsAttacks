// Description and draft code
/*
_____DESCRIPTION_____

Space Invaders:
(from: http://www.classicgaming.cc/classics/space-invaders/play-guide)

The object of the game is to shoot the invaders with your missile base while avoiding their shots and preventing an invasion.
Amassing a high score is a further objective and one that must be prioritised against your continued survival.
Each game screen starts with five rows of 11 invaders.
The bottom 2 rows score 10 points per large invader, the middle 2 rows 20 points for each medium invader and the top row scores 30 points for
each small invader. This makes each screen worth a total of 990 points.
The score for each screen can be dramatically increased by the destruction of the 'mystery' value spaceships that frequently fly from
one side of the screen to the other. The mystery ufo should have a points value of 50 to 200 points.
Temporary sanctuary can be sought beneath the 4 base shields. Shields are destructable by both the player and the aliens. Only the part of the
shield hit by either a player missile or an alien bomb should be destroyed not the entire shield.

The invaders travel sideways and each time they touch the side they drop down 1 line.
On level 1 they need to drop 11 lines to reach the bottom and 'invade'.
From level 2 through to screen 9 they start progressively lower down the screen.
At screen 10 the game reverts to the screen 1 start position and the cycle begins again.

There is no time limit, except for the fact that if you do not shoot them all before they reach the bottom of the screen the game ends.

The more invaders the player shoots, the faster the remaining invaders move.
When the invaders are low enough to touch the base shelters they erase them as they pass. The last invader moves very quickly.

Any bombs dropped by an invader on the row above 'invasion' row will not harm the player's missile.

The aliens can have a maximum of 3 bombs on screen at any one time. The player can have only 1 missile shot on screen at any one time.

If the player is hit, the game should pause, and the player should be showing the exploding animation.

If an alien is hit, they should explode for a short period of time then disappear.

There should be an intro screen, game over screen (where the player can enter their name), and high score screen

There should be a high score table that can be seen from the initial welcome screen and after the game is over and the player enters his/her 3 letter name


All regular aliens are 2 by 4 in terms of size (2 rows of 4 columns)
Player is 2 by 5
Alien UFO is 2 by 6

Alien sprites:
30 point aliens:  /oo\  /oo\
				  <  >  /""\

20 point aliens:  ><  |><|
				 |\/| /  \

10 point aliens: /--\  /--\
				 /  \  <  >

Alien Explosion: \||/
				 /||\

alien bombs: \ | / -

Alien UFO: _/oo\_
		   =q==p=

Player sprite:  =A=
			   =====
					0    1
Player explosion: ,~^.' '+-`.
				  ===== =====

Shield: /IIIII\
		IIIIIII
		I/   \I

General Data:
-------------
Player
Aliens
Shields
Alien bombs
Player missiles
Game states
Scores
High Score table

Player
------
Position
Missile - position
Animation State
Size of the sprite
Lives (3)
Score

Shields
-------
Sprite - the sprite can change
Position

Alien Swarm (all the 10, 20, and 30 point aliens)
-----------
Position
direction (left or right)
animation state
size of each alien
State of each alien - alive, dead, or exploding
Alien bombs

Alien UFO
---------
size
position
points

Position
--------
x, y coordinate

Alien Bomb
---------
position
animation state - \ | / -

Missile (sprite - |)
-------
Position

Game
-----
Game State
Level
size of the window

Score
-----
score value
name

High Score table
----------------
vector of scores

*/

#pragma once

#include "StaticLib-Utils.h"

#include "Game.h"
#include "Player.h"
#include "Shield.h"
#include "AlienSwarm.h"
#include "AlienUFO.h"
#include "Score.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // Random numbers generation

using std::cin;
using std::cout;
using std::endl;
using std::string;

std::vector<Shield> iniShields(const Game& game, const Player& player);

int handleInput(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo, std::vector<Score>& high_score_table); // Returns int value due to Arrow keys
void updateGame(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo);
void drawGame(const Game& game, const Player& player, const std::vector<Shield>& shields, const AlienSwarm& aliens, const AlienUFO& ufo, const std::vector<Score>& high_score_table);

void handleInputI(Game& game);
void handleInputLeft(Game& game, Player& player);
void handleInputRight(Game& game, Player& player);
void handleInputUp(Game& game);
void handleInputDown(Game& game);
void handleInputSpace(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo, std::vector<Score>& high_score_table);

void updateMissile(Player& player, std::vector<Shield>& shields);
void updateAlienSwarm(Game& game, Player& player, AlienSwarm& alien_swarm, std::vector<Shield>& shields);
void updateUFO(const Game& game, Player& player, AlienUFO& ufo);

void drawIntroScreen(const Game& game);
void drawInstructionsScreen1(const Game& game);
void drawInstructionsScreen2(const Game& game);
void drawGameOverScreen(const Game& game);
void drawHighScoresScreen(const Game& game, const std::vector<Score>& high_score_table);

void drawShields(const std::vector<Shield>& shields);
void drawAlienSwarm(const AlienSwarm& alien_swarm);
void drawBombs(const AlienSwarm& alien_swarm);
void drawGameStats(const Game& game, const Player& player);
void drawHighScoreTable(const Game& game, const std::vector<Score>& high_score_table, const int& y_pos, int& y_pos_end);

void resetLevel(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo);
void resetGame(Game& game, Player& player, std::vector<Shield>& shields, AlienSwarm& alien_swarm, AlienUFO& ufo);
void resetShields(const Game& game, const Player& player, std::vector<Shield>& shields);

void checkResolveShieldsMissileCollision(Player& player, std::vector<Shield>& shields);
bool isShieldCollision(const Position& projectile, const Shield& shield, Position& shield_collision_point); // Return true if collision and return shield collision point
void resolveShieldCollision(Shield& shield, const Position& shield_collision_point);

void checkResolveAlienSwarmMissileCollision(Player& player, AlienSwarm& alien_swarm); // It also increments player's score
bool isAlienMissileCollision(const Position& projectile, const Alien& alien); // Return true if collision
void resolveAlienMissileCollision(Player& player, Alien& alien); // Alien starts exploding and player get points

void updateAlienSwarmExplosions(AlienSwarm& alien_swarm);

void updateAlienSwarmMovementShieldCollisionAndShooting(Game& game, AlienSwarm& alien_swarm, std::vector<Shield>& shields); // Move alien swarm taking into account shield collision and shoot
void checkResolveAlienSwarmShieldsCollision(const AlienSwarm& alien_swarm, std::vector<Shield>& shields);
void collideShieldsWithAlien(std::vector<Shield>& shields, Alien& alien);

void updateAlienSwarmBombs(const Game& game, AlienSwarm& alien_swarm, std::vector<Shield>& shields, Player& player);
void checkResolveShieldsBombCollision(AlienSwarm& alien_swarm, AlienBomb& bomb, std::vector<Shield>& shields);
void checkResolvePlayerBombCollision(AlienSwarm& alien_swarm, AlienBomb& bomb, Player& player);
bool isCollision(const Position& projectile, const Position& object_position, const Size& object_size);

void checkResolveUFOMissileCollision(Player& player, AlienUFO& ufo);

void addScore(std::vector<Score>& high_score_table, const std::string& name, const int& score);
bool scoreCompare(const Score& score_1, const Score& score_2); // Descending order

/// <summary>
/// ////////////////////////////////////////////////////
/// </summary>