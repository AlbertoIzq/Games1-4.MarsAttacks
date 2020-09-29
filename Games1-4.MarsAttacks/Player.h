#pragma once

#include "MovingObject.h"

#include "Missile.h"
#include "Game.h"

class Player : public MovingObject
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X;
	static const int DEF_INI_POSITION_Y;
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 5 };
	static constexpr int DEF_SPRITE_HEIGHT{ 2 };
	static const std::vector<std::string> DEF_SPRITE; // Initialized in .cpp
	static constexpr int DEF_SPEED{ 2 };
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
	static constexpr int DEF_SPEED_MISSILE{ 2 };
protected:
	Missile missile;
	int lives;
	//int score;
	//int animation

	void resetPosition();
public:
	Player();
	virtual ~Player() = default;

	// GET METHODS
	inline Missile getMissile() const { return missile; }
	inline int getLives() const { return lives; }

	// SET METHODS
	void move(const Game& game, const bool& direction_right);
	void shootMissile();
	void moveMissile();
};



