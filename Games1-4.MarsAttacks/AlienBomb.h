#pragma once

#include "MovingObject.h"

class AlienBomb : public MovingObject
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_X{ DEF_NOT_IN_PLAY };
	static constexpr int DEF_INI_POSITION_Y{ DEF_NOT_IN_PLAY };
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 1 };
	static constexpr int DEF_SPRITE_HEIGHT{ 1 };
	static const std::vector<std::string> DEF_SPRITE_1; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_2; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_3; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_4; // Initialized in .cpp
	static constexpr int DEF_SPEED{ 2 };
protected:
public:
	AlienBomb();
	virtual ~AlienBomb() = default;

	virtual void draw() const override;

	void reset();
};