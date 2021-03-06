#include "Player.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const int Player::DEF_INI_POSITION_X = (Game::DEF_WINDOW_SIZE.width - DEF_SPRITE_WIDTH) / 2;
const int Player::DEF_INI_POSITION_Y = Game::DEF_WINDOW_SIZE.height - DEF_SPRITE_HEIGHT - DEF_POSITION_Y_OFFSET_DOWN;
const Position Player::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Player::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Player::DEF_SPRITE{ " =A= ", "=====" };
const std::vector<std::string> Player::DEF_SPRITE_DEAD_1{ ",~^.'", "====="  };
const std::vector<std::string> Player::DEF_SPRITE_DEAD_2{ "'+-`.", "====="  };

Player::Player()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE, DEF_SPEED }, lives{ DEF_MAX_NUM_LIVES }, score{ DEF_INI_SCORE }, isShootingMissile{ false }, isShot{false} {
}

void Player::move(const Game& game, const bool& direction_right) {
	int dx{ 0 };
	if (direction_right) {
		dx = DEF_SPEED;
	}
	else {
		dx = -DEF_SPEED;
	}
	if (position.x + spriteSize.width + dx > game.getWindowSize().width) // Make sure the player doesn't go off the screen to the right
	{
		position.x = game.getWindowSize().width - spriteSize.width; // The most right position the player can be
	}
	else if (position.x + dx < 0) // Make sure the player doesn't go off the screen to the left
	{
		position.x = 0;
	}
	else {
		position.x += dx;
	}
}

void Player::gotShot() {
	isShot = true;
	lives--;
	sprite = DEF_SPRITE_DEAD_1;
}

void Player::changeDeadSprite() {
	if (sprite == DEF_SPRITE_DEAD_1)
		sprite = DEF_SPRITE_DEAD_2;
	else if (sprite == DEF_SPRITE_DEAD_2)
		sprite = DEF_SPRITE_DEAD_1;
}


void Player::shootMissile() {
	if (missile.getPosition().y == DEF_NOT_IN_PLAY || missile.getPosition().x == DEF_NOT_IN_PLAY)
	{
		isShootingMissile = true;
		missile.setPosition(getPosition().x + getSpriteSize().width / 2, getPosition().y - 1); // In the middle of the player, one row above
	}
}

void Player::moveMissile() {
	if (missile.getPosition().y != DEF_NOT_IN_PLAY || missile.getPosition().x != DEF_NOT_IN_PLAY)
	{
		if (!isShootingMissile) {
			missile.setPosition(missile.getPosition().x, missile.getPosition().y - missile.getSpeed());
		}
		else {
			isShootingMissile = false;
		}
		if (missile.getPosition().y < 0) { // When the missile is off the screen
			missile.reset();
		}
	}
}

void Player::resetLevel() {
	position = DEF_INI_POSITION;
	sprite = DEF_SPRITE;
	missile.reset();
	isShootingMissile = false;
	isShot = false;
}

void Player::resetAll() {
	resetLevel();
	lives = DEF_MAX_NUM_LIVES;
	score = DEF_INI_SCORE;
}