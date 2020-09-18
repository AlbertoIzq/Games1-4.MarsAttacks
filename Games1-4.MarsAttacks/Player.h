#pragma once
#include "Games1-4.MarsAttacks.h" // Needed for Position

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
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
	static const Position DEF_INITIAL_POSITION;
protected:
	Position position;
	int lives;
public:
	Player();
};

