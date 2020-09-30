#include "Player.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const int Player::DEF_INI_POSITION_X = (Game::DEF_WINDOW_SIZE.width - DEF_SPRITE_WIDTH) / 2;
const int Player::DEF_INI_POSITION_Y = Game::DEF_WINDOW_SIZE.height - DEF_SPRITE_HEIGHT - 1;
const Position Player::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Player::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Player::DEF_SPRITE{ " =A= ", "=====" };

Player::Player()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE, DEF_SPEED }, lives{ DEF_MAX_NUM_LIVES }, isShootingMissile{ false } {
}

void Player::resetPosition() {
	position = DEF_INI_POSITION;
	//animation = 0;
	//missile =
	//resetMissile
}

void Player::move(const Game& game, const bool& direction_right) {
	int dx{ 0 };
	if (direction_right) {
		dx = DEF_SPEED;
	}
	else {
		dx = -DEF_SPEED;
	}
	if (position.x + spriteSize.width + dx > game.getSize().width) // Make sure the player doesn't go off the screen to the right
	{
		position.x = game.getSize().width - spriteSize.width; // The most right position the player can be
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
	if (missile.getPosition().y == DEF_NOT_IN_PLAY || missile.getPosition().x == DEF_NOT_IN_PLAY)
	{
		isShootingMissile = true;
		missile.setPosition(getPosition().x + getSpriteSize().width / 2, getPosition().y - 1); // In the middle of the player, one row above
	}
}

void Player::moveMissile() {
	if (missile.getPosition().y != DEF_NOT_IN_PLAY)
	{
		if (!isShootingMissile) {
			missile.setPosition(missile.getPosition().x, missile.getPosition().y - missile.getSpeed());
		}
		else {
			isShootingMissile = false;
		}
		if (missile.getPosition().y < 0) {
			resetMissile();
		}
	}
}

void Player::resetMissile() {
	missile.setPosition(DEF_NOT_IN_PLAY, DEF_NOT_IN_PLAY);
}