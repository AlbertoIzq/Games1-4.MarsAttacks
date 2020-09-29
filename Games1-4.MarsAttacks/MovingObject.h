#pragma once

#include "StaticObject.h"

class MovingObject : public StaticObject
{
protected:
	int speed;
public:
	MovingObject(Position position_val, Size size_val, std::vector<std::string> sprite_val, int speed_val);
	virtual ~MovingObject() = default;

	// GET METHODS
	inline int getSpeed() const { return speed; }

	// SET METHODS
	inline void setSpeed(const int& speed) { this->speed = speed; }
};