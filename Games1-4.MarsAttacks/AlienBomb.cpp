#include "AlienBomb.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position AlienBomb::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size AlienBomb::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> AlienBomb::DEF_SPRITE_1{ "|" };
const std::vector<std::string> AlienBomb::DEF_SPRITE_2{ "/" };
const std::vector<std::string> AlienBomb::DEF_SPRITE_3{ "-" };
const std::vector<std::string> AlienBomb::DEF_SPRITE_4{ "\\" };

AlienBomb::AlienBomb()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE_1, DEF_SPEED }, animation{ 1 } {
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

void AlienBomb::updateAnimation() {
	animation++;
	if (animation > 4) {
		animation = 1;
	}
}

void AlienBomb::setSpriteDependingOnAnimation() {
	switch (animation) {
	case 1:
		sprite = DEF_SPRITE_1;
		break;
	case 2:
		sprite = DEF_SPRITE_2;
		break;
	case 3:
		sprite = DEF_SPRITE_3;
		break;
	case 4:
		sprite = DEF_SPRITE_4;
		break;
	}
}