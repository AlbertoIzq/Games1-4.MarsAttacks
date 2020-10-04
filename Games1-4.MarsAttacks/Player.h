#pragma once

#include "MovingObject.h"

#include "Missile.h"
#include "Game.h"

class Player : public MovingObject
{
public:
	static const std::vector<std::string> DEF_SPRITE; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_DEAD_1; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_DEAD_2; // Initialized in .cpp
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X;
	static const int DEF_INI_POSITION_Y;
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 5 };
	static constexpr int DEF_SPRITE_HEIGHT{ 2 };
	static constexpr int DEF_SPEED{ 1 };
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
	static constexpr int DEF_INI_SCORE{ 0 };
protected:
	Missile missile;
	int lives;
	int score;

	bool isShootingMissile;
	bool isShot;

public:
	Player();
	virtual ~Player() = default;

	// GET METHODS
	inline Missile getMissile() const { return missile; }
	inline int getLives() const { return lives; }
	inline int getScore() const { return score; }
	inline bool getIsShot() const { return isShot; }

	// SET METHODS
	inline Missile& setMissile() { return missile; }
	inline void setLives(const int& lives) { this->lives = lives; };
	inline void setScore(const int& score) { this->score = score; };
	inline void setIsShot(const bool& is_shot) { isShot = is_shot; }

	void move(const Game& game, const bool& direction_right);
	void resetPosition();
	void gotShot();
	void changeDeadSprite();

	void shootMissile();
	void moveMissile();
};