#include "Player.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const int Player::DEF_INI_POSITION_X = (Game::DEF_WINDOW.width - DEF_SPRITE_WIDTH) / 2;
const int Player::DEF_INI_POSITION_Y = Game::DEF_WINDOW.height - DEF_SPRITE_WIDTH - DEF_INI_POSITION_Y_OFFSET_DOWN;
const Position Player::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Player::DEF_SPRITE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };

Player::Player()
	: position{ DEF_INI_POSITION }, spriteSize{ DEF_SPRITE }, lives{ DEF_MAX_NUM_LIVES } {
}

void Player::resetPosition() {
	position = DEF_INI_POSITION;
	//animation = 0;
	//missile =
	//resetMissile
}