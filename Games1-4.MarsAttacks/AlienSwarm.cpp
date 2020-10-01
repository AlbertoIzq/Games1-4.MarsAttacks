#include "AlienSwarm.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const int AlienSwarm::DEF_INI_POSITION_X = (Game::DEF_WINDOW_SIZE.width - DEF_NUM_COLS * (Alien::DEF_SPRITE_WIDTH + DEF_PADDING_X)) / 2;
const int AlienSwarm::DEF_INI_POSITION_Y = Game::DEF_WINDOW_SIZE.height - DEF_NUM_COLS - DEF_NUM_ROWS * Alien::DEF_SPRITE_HEIGHT - DEF_PADDING_Y * (DEF_NUM_ROWS - 1) - 3; //+game.level;
const Position AlienSwarm::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };

AlienSwarm::AlienSwarm(const Game& game)
	: position{ DEF_INI_POSITION }, numAliensLeft{ 0 }, directionRight{ true } {
	//position.y += game.level;

	// 1 row - 30 Points aliens
	for (int row{ 0 }; row < DEF_NUM_ROWS_30P; row++) {
		std::vector<Alien> alien_30P;
		for (int col{ 0 }; col < DEF_NUM_COLS; col++) {
			Alien alien;
			alien.setPosition(position.x + col * (Alien::DEF_SPRITE_WIDTH + DEF_PADDING_X),
							  position.y);
			alien.setAlienType(Alien_Type::AT_30P);
			alien.setSprite(Alien::DEF_SPRITE_30P_1);
			alien_30P.push_back(alien);
			numAliensLeft++;
		}
		aliens.push_back(alien_30P);
	}

	// 2 rows - 20 Points aliens
	for (int row{ 0 }; row < DEF_NUM_ROWS_20P; row++) {
		std::vector<Alien> alien_20P;
		for (int col{ 0 }; col < DEF_NUM_COLS; col++) {
			Alien alien;
			alien.setPosition(position.x + col * (Alien::DEF_SPRITE_WIDTH + DEF_PADDING_X),
							  position.y + row * (Alien::DEF_SPRITE_HEIGHT + DEF_PADDING_Y) + DEF_NUM_ROWS_30P * (Alien::DEF_SPRITE_HEIGHT + DEF_PADDING_Y));
			alien.setAlienType(Alien_Type::AT_20P);
			alien.setSprite(Alien::DEF_SPRITE_20P_1);
			alien_20P.push_back(alien);
			numAliensLeft++;
		}
		aliens.push_back(alien_20P);
	}

	// 2 rows - 10 Points aliens
	for (int row{ 0 }; row < DEF_NUM_ROWS_10P; row++) {
		std::vector<Alien> alien_10P;
		for (int col{ 0 }; col < DEF_NUM_COLS; col++) {
			Alien alien;
			alien.setPosition(position.x + col * (Alien::DEF_SPRITE_WIDTH + DEF_PADDING_X),
							  position.y + row * (Alien::DEF_SPRITE_HEIGHT + DEF_PADDING_Y) + DEF_NUM_ROWS_30P * (Alien::DEF_SPRITE_HEIGHT + DEF_PADDING_Y) + DEF_NUM_ROWS_20P * (Alien::DEF_SPRITE_HEIGHT + DEF_PADDING_Y));
			alien.setAlienType(Alien_Type::AT_10P);
			alien.setSprite(Alien::DEF_SPRITE_10P_1);
			alien_10P.push_back(alien);
			numAliensLeft++;
		}
		aliens.push_back(alien_10P);
	}

	resetMovementTimer();
	line = DEF_NUM_COLS - game.getLevel() - 1;
}

void AlienSwarm::setPositionDiff(const int& dx, const int& dy) {
	// Change position for alien swarm
	position.x += dx;
	position.y += dy;

	// Update position and change animation for all aliens belonging to alien swarm
	for (auto& alien_row : aliens) {
		for (auto& alien : alien_row) {
			alien.setPosition(alien.getPosition().x + dx, alien.getPosition().y + dy);
			if (alien.getAnimation() == 1) {
				alien.setAnimation(2);
			}
			else { // animation == 2
				alien.setAnimation(1);
			}
		}
	}
}

void AlienSwarm::resetMovementTimer() {
	movementTimer = line * 2 + (5 * (static_cast<float>(numAliensLeft) / static_cast<float>(DEF_NUM_COLS * DEF_NUM_ROWS)));
}

void AlienSwarm::getAlienLeftRightBottom(Alien& alien_left, Alien& alien_right, Alien& alien_bottom) const {
	bool found{ false };

	for (int col{ 0 }; col < DEF_NUM_COLS && !found; col++) {
		for (int row{ 0 }; row < DEF_NUM_ROWS && !found; row++) {
			if (aliens.at(row).at(col).getAlienState() != Alien_State::AS_DEAD) {
				alien_left = aliens.at(row).at(col);
				found = true;	
			}
		}
	}
	found = false;

	for (int col{ DEF_NUM_COLS - 1 }; col >= 0 && !found; col--) {
		for (int row{ 0 }; row < DEF_NUM_ROWS && !found; row++) {
			if (aliens.at(row).at(col).getAlienState() != Alien_State::AS_DEAD) {
				alien_right = aliens.at(row).at(col);
				found = true;
			}
		}
	}
	found = false;

	for (int row{ DEF_NUM_ROWS - 1 }; row >= 0 && !found; row--) {
		for (int col{ 0 }; col < DEF_NUM_COLS && !found; col++) {
			if (aliens.at(row).at(col).getAlienState() != Alien_State::AS_DEAD) {
				alien_bottom = aliens.at(row).at(col);
				found = true;
			}
		}
	}
	found = false;
}