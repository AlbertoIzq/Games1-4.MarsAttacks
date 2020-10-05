#include "AlienUFO.h"

// Initialization of class structs default values (They cannot be initialized in Player.h)
const Position AlienUFO::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size AlienUFO::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> AlienUFO::DEF_SPRITE{ "_/oo\\_", "=q==p=" };

AlienUFO::AlienUFO()
	: MovingObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE, DEF_SPEED } {
	appearTimer = ((rand() % (DEF_APPEAR_TIME_MAX_SEC - DEF_APPEAR_TIME_MIN_SEC + 1)) + DEF_APPEAR_TIME_MIN_SEC) * DEF_FPS;
	points = (rand() % (DEF_MAX_POINTS_NUM) + 1) * DEF_MIN_POINTS;
}

void AlienUFO::draw() const {
	if (position.x != DEF_NOT_IN_PLAY) {
		drawSprite(position.x, position.y, sprite);
	}
}

void AlienUFO::putInPlay() {
	if (position.x == DEF_NOT_IN_PLAY && appearTimer <= 0)
		position.x = 0;
	else
		appearTimer--;
}

void AlienUFO::move(const Game& game) {
	if (position.x != DEF_NOT_IN_PLAY) {
		position.x += speed;
		if (position.x + spriteSize.width >= game.getWindowSize().width) {
			reset();
		}
	}
}

void AlienUFO::reset() {
	position.x = DEF_NOT_IN_PLAY;
	appearTimer = ((rand() % (DEF_APPEAR_TIME_MAX_SEC - DEF_APPEAR_TIME_MIN_SEC + 1)) + DEF_APPEAR_TIME_MIN_SEC) * DEF_FPS;
	points = (rand() % (DEF_MAX_POINTS_NUM)+1) * DEF_MIN_POINTS;
}