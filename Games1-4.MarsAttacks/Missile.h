#pragma once

#include "Other.h" // Needed for Position, Size and PDCursesUtils

#include <array>
#include <string>

class Missile
{
public:
	static constexpr int POSITION_NOT_IN_PLAY{ -1 };
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X{ POSITION_NOT_IN_PLAY };
	static const int DEF_INI_POSITION_Y{ POSITION_NOT_IN_PLAY };
	static constexpr char MISSILE_SPRITE{ '|' };
	static constexpr int DEF_SPEED{ 1 };
protected:
	Position position;
	char sprite;
public:
	Missile();
	
	// GET METHODS
	Position getPosition() const { return position; }
	char getSprite() const { return sprite; }

	// SET METHODS
	void setPosition(const int& x_pos, const int& y_pos) { position.x = x_pos; position.y = y_pos; }

	void draw() const;
};