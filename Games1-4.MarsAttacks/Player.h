#pragma once

#include "Games1-4.MarsAttacks.h" // Needed for Position and Size

/*struct Player {
	Position position;
	Position missile;
	Size spriteSize;
	int animation;
	int lives; // max 3
	int score;
};*/

class Player
{
private:
	static const Position DEF_INITIAL_POSITION; // Initialized in .cpp
	static const Size DEF_SPRITE; // Initialized in .cpp
	static const int DEF_SPRITE_WIDTH{ 5 };
	static const int DEF_SPRITE_HEIGTH{ 2 };
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
protected:
	Position position;
	Size spriteSize;
	int lives;
public:
	Player();
};

