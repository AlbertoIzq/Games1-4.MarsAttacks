#pragma once

#include "MovingObject.h"

class Shield : public StaticObject
{
public:
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_POSITION_Y_OFFSET_DOWN_PLAYER{ 2 };
	static constexpr int DEF_NUM_SHIELDS{ 4 };
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_X{ DEF_NOT_IN_PLAY };
	static constexpr int DEF_INI_POSITION_Y{ DEF_NOT_IN_PLAY };
	static constexpr int DEF_SPRITE_WIDTH{ 7 };
	static constexpr int DEF_SPRITE_HEIGHT{ 3 };
	static const std::vector<std::string> DEF_SPRITE; // Initialized in .cpp
public:
	Shield();
	virtual ~Shield() = default;
};