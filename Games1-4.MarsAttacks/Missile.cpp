#include "Missile.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position Missile::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Missile::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Missile::DEF_SPRITE{ "|" };

Missile::Missile()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE, DEF_SPEED } {
}

void Missile::draw() const {
	if (position.x != DEF_NOT_IN_PLAY) {
		drawSprite(position.x, position.y, sprite, spriteSize.height);
	}
}

void Missile::reset() {
	position.x = DEF_NOT_IN_PLAY;
	position.y = DEF_NOT_IN_PLAY;
}