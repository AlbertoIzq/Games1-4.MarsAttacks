#include "StaticObject.h"

StaticObject::StaticObject(Position positionVal, Size sizeVal, std::vector<std::string> spriteVal)
	: position{ positionVal }, spriteSize{ sizeVal }, sprite{ spriteVal } {
}

void StaticObject::draw() const {
	drawSprite(position.x, position.y, sprite, spriteSize.height);
}