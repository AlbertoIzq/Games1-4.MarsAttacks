#include "Player.h"

const Position Player::DEF_INITIAL_POSITION{ 0, 0 };

Player::Player()
	: position{DEF_INITIAL_POSITION}, lives{ DEF_MAX_NUM_LIVES } {
}