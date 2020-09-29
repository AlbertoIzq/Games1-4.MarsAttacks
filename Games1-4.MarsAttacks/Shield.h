#pragma once

#include "MovingObject.h"

class Shield : public StaticObject
{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_X{ POSITION_NOT_IN_PLAY };
	static constexpr int DEF_INI_POSITION_Y{ POSITION_NOT_IN_PLAY };
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 7 };
	static constexpr int DEF_SPRITE_HEIGHT{ 3 };
	static const std::vector<std::string> DEF_SPRITE; // Initialized in .cpp
public:
	Shield();
	virtual ~Shield() = default;
};

