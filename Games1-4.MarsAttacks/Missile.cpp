#include "Missile.h"

#include <iostream>

// Initialization of class structs default values (They cannot be initialized in Player.h)
const Position Missile::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };

Missile::Missile()
	: position{ DEF_INI_POSITION }, sprite{ MISSILE_SPRITE } {
}

void Missile::draw() const {
	if (position.x != POSITION_NOT_IN_PLAY) {
		drawCharacter(position.x, position.y, sprite);
	}
}