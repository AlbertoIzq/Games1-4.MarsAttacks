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
	int numAliensLeft;
	bool directionRight; // True if direction = right, false if direction = left, (> 0 means right in tutorial)
	int movementTimer; // This is going to capture how fast the aliens should be going
	int line; // This is to capture when the aliens win - starts at the current level and decreases to 0 - once it's 0 then the aliens
public:
	AlienSwarm(const Game& game);

	// GET METHODS
	inline Position getPosition() const { return position; }
	inline std::vector<std::vector<Alien>> getAliens() const { return aliens; }
	inline int getNumAliensLeft() const { return numAliensLeft; }
	inline bool getDirectionRight() const { return directionRight; }
	inline int getMovementTimer() const { return movementTimer; }
	inline int getLine() const { return line; }

	// SET METHODS
	void setPositionDiff(const int& dx, const int& dy);
	inline std::vector<std::vector<Alien>>& setAliens() { return aliens; }
	inline void setNumAliensLeft(const int& num_aliens_left) { numAliensLeft = num_aliens_left; }
	inline void setDirectionRight(const bool& direction_right) { directionRight = direction_right; }
	inline void setMovementTimer(const int& movement_timer) { movementTimer = movement_timer; }
	inline void setLine(const int& line) { this->line = line; }

	void resetMovementTimer();
	void getAlienLeftRightBottom(Alien& alien_left, Alien& alien_right, Alien& alien_bottom) const;
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
	AlienState aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLS];
	AlienBomb bombs[MAX_NUM_ALIEN_BOMBS];
	Size spriteSize;
	int numberOfBombsInPlay;
};

INIT ALIENS

	direction = right
	numAliensLeft = num aliens rows * num aliens cols
	animation = 0
	numberOfBombsInPlay = 0
	position.x = game.windowSize.width - NUM_ALIENS_COLS * aliens.spriteSize.width / 2;
	position.y = game.windowSize.heigth - NUM_ALIENS_COLS - NUMS_ALIENS_ROWS * aliens.spriteSize.heigth - NUM_ALIENS_ROWS - 1 - 3 + game.level
*/