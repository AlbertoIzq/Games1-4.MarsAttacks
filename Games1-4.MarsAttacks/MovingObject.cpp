#include "MovingObject.h"

MovingObject::MovingObject(Position position_val, Size size_val, std::vector<std::string> sprite_val, int speed_val)
	: StaticObject{ position_val, size_val, sprite_val }, speed{ speed_val } {
}