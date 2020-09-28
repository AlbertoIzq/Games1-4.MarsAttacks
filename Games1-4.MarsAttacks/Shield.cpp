#include "Shield.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const Position Shield::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Shield::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::array<std::string, Shield::DEF_SPRITE_HEIGHT> Shield::SHIELD_SPRITE{ "/IIIII\\", "IIIIIII", "I/   \\I"};

Shield::Shield()
	: position{ DEF_INI_POSITION }, spriteSize{ DEF_SPRITE_SIZE }, sprite{ SHIELD_SPRITE } {
}

void Shield::draw() const {
	drawSprite(position.x, position.y, sprite, spriteSize.height);
}