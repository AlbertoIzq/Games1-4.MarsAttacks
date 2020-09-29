#include "MovingObject.h"

MovingObject::MovingObject(Position positionVal, Size sizeVal, std::vector<std::string> spriteVal, int speedVal)
	: StaticObject{ positionVal, sizeVal, spriteVal }, speed{ speedVal } {
}