#include "AlienBomb.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position AlienBomb::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size AlienBomb::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> AlienBomb::DEF_SPRITE{ "*" };

AlienBomb::AlienBomb()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE, DEF_SPEED } {
}

void AlienBomb::draw() const {
	if (position.x != DEF_NOT_IN_PLAY) {
		drawSprite(position.x, position.y, sprite, spriteSize.height);
	}
}

void AlienBomb::reset() {
	position.x = DEF_NOT_IN_PLAY;
	position.y = DEF_NOT_IN_PLAY;
}