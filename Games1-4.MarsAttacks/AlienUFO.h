#pragma once

#include "MovingObject.h"
#include "Game.h"

class AlienUFO : public MovingObject
{
public:
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_EXPLOSION_TIME{ 8 };
	static const std::vector<std::string> DEF_SPRITE_EXPLOSION;
private:
	static const std::vector<std::string> DEF_SPRITE; // Initialized in .cpp
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_X{ DEF_NOT_IN_PLAY };
	static constexpr int DEF_INI_POSITION_Y{ 2 };
	static constexpr int DEF_SPRITE_WIDTH{ 6 };
	static constexpr int DEF_SPRITE_HEIGHT{ 2 };
	static constexpr int DEF_SPEED{ 1 };
	static constexpr int DEF_MIN_POINTS{ 50 };
	static constexpr int DEF_MAX_POINTS_NUM{ 4 };
	static constexpr int DEF_APPEAR_TIME_MIN_SEC{ 10 };
	static constexpr int DEF_APPEAR_TIME_MAX_SEC{ 30 };
protected:
	int appearTimer;
	int points;
	int explosionTimer;

	bool exploding;
public:
	AlienUFO();
	virtual ~AlienUFO() = default;

	virtual void draw() const override;

	// GET METHODS
	inline int getPoints() const { return points; }
	inline int getExplosionTimer() const { return explosionTimer; }

	// SET METHODS
	inline void setExplosionTimer(const int& explosion_timer) { explosionTimer = explosion_timer; }
	inline void setExploding(const bool& exploding) { this->exploding = exploding; }

	void putInPlay();
	void move(const Game& game);
	void reset();
	void updateExplosion();
};