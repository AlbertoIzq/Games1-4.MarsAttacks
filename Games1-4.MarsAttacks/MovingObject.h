#pragma once

#include "StaticObject.h"

class MovingObject : public StaticObject
{
protected:
	int speed;
public:
	MovingObject(Position positionVal, Size sizeVal, std::vector<std::string> spriteVal, int speedVal);
	virtual ~MovingObject() = default;

	// GET METHODS
	inline int getSpeed() const { return speed; }

	// SET METHODS
	inline void setSpeed(const int& speed) { this->speed = speed; }
};