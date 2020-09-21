#pragma once

#include "Game.h"
#include "Other.h" // Needed for Position and Size

/*struct Player {
	Position position;
	Position missile;
	Size spriteSize;
	int animation;
	int lives; // max 3
	int score;
};*/

/*
CONSTANTS

NOT_IN_PLAY = 1;

void resetMissile(Player& player) {
	player.missile.x = NOT_IN_PLAY;
	player.missile.y = NOT_IN_PLAY;
}
*/

class Player
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X; // Initialized in .cpp
	static const int DEF_INI_POSITION_Y; // Initialized in .cpp
	static const int DEF_INI_POSITION_Y_OFFSET_DOWN{ 1 };
	static const Size DEF_SPRITE; // Initialized in .cpp
	static const int DEF_SPRITE_WIDTH{ 5 };
	static const int DEF_SPRITE_HEIGHT{ 2 };
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
protected:
	Position position;
	Size spriteSize;
	int lives;

	void resetPosition();
public:
	Player();
};

