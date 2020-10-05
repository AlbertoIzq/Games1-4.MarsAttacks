#pragma once

#include "Game.h"
#include "Alien.h"
#include "AlienBomb.h"
#include "Shield.h"
#include "Player.h"
#include "Other.h" // Needed for Position, Size and PDCursesUtils

#include <vector>

class AlienSwarm
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X;
	static const int DEF_INI_POSITION_Y;
	static constexpr int DEF_NUM_COLS{ 11 };
	static constexpr int DEF_NUM_ROWS{ 5 };
	static constexpr int DEF_NUM_ROWS_30P{ 1 };
	static constexpr int DEF_NUM_ROWS_20P{ 2 };
	static constexpr int DEF_NUM_ROWS_10P{ 2 };
	static constexpr int DEF_PADDING_X{ 1 };
	static constexpr int DEF_PADDING_Y{ 1 };
	static constexpr int DEF_MAX_NUM_BOMBS{ 3 };
protected:
	Position position;
	std::vector<std::vector<Alien>> aliens;
	int numAliensLeft;
	bool directionRight; // True if direction = right, false if direction = left, (> 0 means right in tutorial)
	int movementTimer; // This is going to capture how fast the aliens should be going
	int line; // This is to capture when the aliens win - starts at the current level and decreases to 0 - once it's 0 then the aliens
	std::vector<AlienBomb> bombs;
	int numBombsInPlay;

	bool isShootingBomb;

public:
	AlienSwarm(const Game& game);

	// GET METHODS
	inline Position getPosition() const { return position; }
	inline std::vector<std::vector<Alien>> getAliens() const { return aliens; }
	inline int getNumAliensLeft() const { return numAliensLeft; }
	inline bool getDirectionRight() const { return directionRight; }
	inline int getMovementTimer() const { return movementTimer; }
	inline int getLine() const { return line; }
	inline std::vector<AlienBomb> getBombs() const { return bombs; }
	inline int getNumBombsInPlay() const { return numBombsInPlay; }

	// SET METHODS
	void setPositionDiff(const int& dx, const int& dy);
	inline std::vector<std::vector<Alien>>& setAliens() { return aliens; }
	inline void setNumAliensLeft(const int& num_aliens_left) { numAliensLeft = num_aliens_left; }
	inline void setDirectionRight(const bool& direction_right) { directionRight = direction_right; }
	inline void setMovementTimer(const int& movement_timer) { movementTimer = movement_timer; }
	inline void setLine(const int& line) { this->line = line; }
	inline std::vector<AlienBomb>& setBombs() { return bombs; }
	inline void setNumBombsInPlay(const int& num_bombs_in_play) { numBombsInPlay = num_bombs_in_play; }

	void resetMovementTimer();
	void getAlienLeftRightBottom(Alien& alien_left, Alien& alien_right, Alien& alien_bottom) const;
	bool shouldShootBomb();
	bool getAlienToShootBomb(Alien& alien); // Returns true if there is an alien available to shoot
	void shootBomb(const Alien& alien);
	void moveChangeAnimationBombs(const Game& game);
	void reset(const Game& game);
};