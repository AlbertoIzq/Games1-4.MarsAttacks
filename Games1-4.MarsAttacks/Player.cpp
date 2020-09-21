#include "Player.h"

// Initialization of class struct default values
const Position Player::DEF_INITIAL_POSITION{ 0, 0 };
const Size Player::DEF_SPRITE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGTH };

Player::Player()
	: position{ DEF_INITIAL_POSITION }, spriteSize{ DEF_SPRITE }, lives{ DEF_MAX_NUM_LIVES } {
}