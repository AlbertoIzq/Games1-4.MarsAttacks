#pragma once

#include "Game.h"
#include "Alien.h"
#include "Other.h" // Needed for Position, Size and PDCursesUtils

#include <vector>

class AlienSwarm
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X;
	static const int DEF_INI_POSITION_Y;
	static constexpr int DEF_NUM_ROWS{ 5 };
	static constexpr int DEF_NUM_COLS{ 11 };
	static constexpr int DEF_NUM_ROWS_30P{ 1 };
	static constexpr int DEF_NUM_ROWS_20P{ 2 };
	static constexpr int DEF_NUM_ROWS_10P{ 2 };
	static constexpr int DEF_PADDING_X{ 1 };
	static constexpr int DEF_PADDING_Y{ 1 };
protected:
	Position position;
	std::vector<std::vector<Alien>> aliens;
public:
	AlienSwarm();//(Game game);

	// GET METHODS
	inline Position getPosition() const { return position; }
	inline std::vector<std::vector<Alien>> getAliens() const { return aliens; }

	// SET METHODS
	inline void setPosition(const int& x, const int& y) { this->position.x = x; this->position.y = y; }

	void draw() const;
};

/*enum {
	MAX_NUM_ALIEN_BOMBS = 3,
};


struct AlienBomb
{
	Position position;
	int animation;
};

struct AlienSwarm {
	Position position;
	AlienState aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS];
	AlienBomb bombs[MAX_NUM_ALIEN_BOMBS];
	Size spriteSize;
	int animation;
	int direction; // > 0 - for going rigth, < 0 - for going left, 1 or -1
	int numberOfBombsInPlay;
	int movementTime; // This is going to capture how fast the aliens should be going
	int explosionTimer; // This is going to capture how long to explode for
	int numAliensLeft; // This is to capture when to go to the next level
	int line; // This is to capture when the aliens win - starts at the current level and decreases to 0 - once it's 0 then the aliens
};

INIT ALIENS

	direction = right
	numAliensLeft = num aliens rows * num aliens cols
	animation = 0
	numberOfBombsInPlay = 0
	position.x = game.windowSize.width - NUM_ALIENS_COLS * aliens.spriteSize.width / 2;
	position.y = game.windowSize.heigth - NUM_ALIENS_COLS - NUMS_ALIENS_ROWS * aliens.spriteSize.heigth - NUM_ALIENS_ROWS - 1 - 3 + game.level
	aliens.line = NUM_ALIENS_COLS - (game.level - 1);
	aliens.explosionTimer = 0;



*/