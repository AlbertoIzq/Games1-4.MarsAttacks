#pragma once

#include "Game.h"
#include "Other.h" // Needed for Position and Size

#include <string>
#include <array>

/*struct Player {
	Position position;
	Position missile;
	Size spriteSize;
	int animation;
	int lives; // max 3
	int score;
};*/

/*
CONSTANTS

NOT_IN_PLAY = 1;

void resetMissile(Player& player) {
	player.missile.x = NOT_IN_PLAY;
	player.missile.y = NOT_IN_PLAY;
}
*/

class Player
{
protected:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static const int DEF_INI_POSITION_X; // Initialized in .cpp
	static const int DEF_INI_POSITION_Y; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_Y_OFFSET_DOWN{ 1 };
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
	static constexpr int DEF_SPRITE_WIDTH{ 5 };
	static constexpr int DEF_SPRITE_HEIGHT{ 2 };
	static const std::array<std::string, DEF_SPRITE_HEIGHT> PLAYER_SPRITE; // Initialized in .cpp
	static constexpr int DEF_MAX_NUM_LIVES{ 3 };
protected:
	Position position;
	Size spriteSize;
	std::array<std::string, DEF_SPRITE_HEIGHT> sprite;
	int lives;

	void resetPosition();
public:
	Player();

	// GET METHODS
	Position getPosition() const { return position; }
	Size getSpriteSize() const { return spriteSize; }
	std::array<std::string, DEF_SPRITE_HEIGHT> getSprite() const { return sprite; }
	int getLives() const { return lives; }

	// SET METHODS
};

