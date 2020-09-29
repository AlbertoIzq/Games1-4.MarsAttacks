#pragma once

#include "Other.h" // Needed for Position, Size and PDCursesUtils
#include <vector>
#include <string>

class StaticObject
{
protected:
	Position position;
	Size spriteSize;
	std::vector<std::string> sprite;
public:
	StaticObject(Position position_val, Size size_val, std::vector<std::string> sprite_val);
	virtual ~StaticObject() = default;

	virtual void draw() const;

	// GET METHODS
	inline Position getPosition() const { return position; }
	inline Size getSpriteSize() const { return spriteSize; }
	inline std::vector<std::string> getSprite() const { return sprite; }

	// SET METHODS
	inline void setPosition(const int& x, const int& y) { this->position.x = x; this->position.y = y; }
	inline void setSprite(const std::vector<std::string>& sprite) { this->sprite = sprite; }
};