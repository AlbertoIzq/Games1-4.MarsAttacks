#include "StaticObject.h"

StaticObject::StaticObject(Position position_val, Size size_val, std::vector<std::string> sprite_val)
	: position{ position_val }, spriteSize{ size_val }, sprite{ sprite_val } {
}

void StaticObject::draw() const {
	drawSprite(position.x, position.y, sprite);
}