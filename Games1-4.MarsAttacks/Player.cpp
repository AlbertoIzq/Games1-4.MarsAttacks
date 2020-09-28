#include "Player.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const int Player::DEF_INI_POSITION_X = (Game::DEF_WINDOW_SIZE.width - DEF_SPRITE_WIDTH) / 2;
const int Player::DEF_INI_POSITION_Y = Game::DEF_WINDOW_SIZE.height - DEF_SPRITE_HEIGHT - DEF_INI_POSITION_Y_OFFSET_DOWN;
const Position Player::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Player::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::array<std::string, Player::DEF_SPRITE_HEIGHT> Player::PLAYER_SPRITE{ " =A= ", "=====" };

Player::Player()
	: position{ DEF_INI_POSITION }, spriteSize{ DEF_SPRITE_SIZE }, sprite{ PLAYER_SPRITE }, missile{ Missile() }, lives{ DEF_MAX_NUM_LIVES } {
}

void Player::resetPosition() {
	position = DEF_INI_POSITION;
	//animation = 0;
	//missile =
	//resetMissile
}

void Player::draw() const {
	drawSprite(position.x, position.y, sprite, spriteSize.height);
}

void Player::move(const Game& game, const bool& direction_right) {
	int dx{ 0 };
	if (direction_right) {
		dx = DEF_SPEED_PLAYER;
	}
	else {
		dx = -DEF_SPEED_PLAYER;
	}
	
	if (position.x + spriteSize.width + dx > game.windowSize.width) // Make sure the player doesn't go off the screen to the right
	{
		position.x = game.windowSize.width - spriteSize.width; // The most right position the player can be
	}
	else if (position.x + dx < 0) // Make sure the player doesn't go off the screen to the left
	{
		position.x = 0;
	}
	else {
		position.x += dx;
	}
}

void Player::shootMissile() {
	if (missile.getPosition().y == missile.POSITION_NOT_IN_PLAY || missile.getPosition().x == missile.POSITION_NOT_IN_PLAY)
	{
		missile.setPosition(getPosition().x + getSpriteSize().width / 2, getPosition().y - 1); // In the middle of the player, one row above
	}
}

void Player::moveMissile() {
	if(missile.getPosition().y != missile.POSITION_NOT_IN_PLAY)
	{
		missile.setPosition(missile.getPosition().x, missile.getPosition().y - DEF_SPEED_MISSILE);
		if (missile.getPosition().y < 0) {
			missile.setPosition(missile.POSITION_NOT_IN_PLAY, missile.POSITION_NOT_IN_PLAY);
		}
	}
}