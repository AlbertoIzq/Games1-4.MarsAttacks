#pragma once

#include "Other.h" // Needed for Position, Size and PDCursesUtils
#include "Game.h"

#include <string>
#include <array>

class Shield {
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X{ -10 };
	static const int DEF_INI_POSITION_Y{ -10 };
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 7 };
	static constexpr int DEF_SPRITE_HEIGHT{ 3 };
	static const std::array<std::string, DEF_SPRITE_HEIGHT> SHIELD_SPRITE; // Initialized in .cpp

protected:
	Position position;
	Size spriteSize;
	std::array<std::string, DEF_SPRITE_HEIGHT> sprite;

public:
	Shield();

	// GET METHODS
	Position getPosition() const { return position; }
	Size getSpriteSize() const { return spriteSize; }
	std::array<std::string, DEF_SPRITE_HEIGHT> getSprite() const { return sprite; }

	// SET METHODS
	void setPosition(const int& x_pos, const int& y_pos) { position.x = x_pos; position.y = y_pos; }

	void draw() const;
};
