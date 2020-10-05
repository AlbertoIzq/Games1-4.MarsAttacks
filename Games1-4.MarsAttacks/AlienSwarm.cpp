#include "AlienSwarm.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const int AlienSwarm::DEF_INI_POSITION_X = (Game::DEF_WINDOW_SIZE.width - DEF_NUM_COLS * (Alien::DEF_SPRITE_WIDTH + DEF_PADDING_X)) / 2;
const int AlienSwarm::DEF_INI_POSITION_Y = Game::DEF_WINDOW_SIZE.height - Player::DEF_POSITION_Y_OFFSET_DOWN - Player::DEF_SPRITE_SIZE.height - Shield::DEF_POSITION_Y_OFFSET_DOWN_PLAYER - Shield::DEF_SPRITE_SIZE.height - (DEF_NUM_ROWS * Alien::DEF_SPRITE_HEIGHT + (DEF_NUM_COLS - 1) * DEF_PADDING_Y);
const Position AlienSwarm::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };

AlienSwarm::AlienSwarm(const Game& game)
	: position{ DEF_INI_POSITION }, numAliensLeft{ 0 }, directionRight{ true }, isShootingBomb{ false }, numBombsInPlay{ 0 } {
	
	position.y += game.getLevel();

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
		}
		aliens.push_back(alien_10P);
	}

	numAliensLeft = DEF_NUM_COLS * DEF_NUM_ROWS;
	resetMovementTimer();
	line = DEF_NUM_COLS - game.getLevel() + 1;

	// Bombs initialization
	for (int i{ 0 }; i < DEF_MAX_NUM_BOMBS; i++) {
		AlienBomb alien_bomb;
		bombs.push_back(alien_bomb);
	}
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

bool AlienSwarm::shouldShootBomb() {
	return static_cast<int>(rand() % (70 - static_cast<int>(static_cast<float>(DEF_NUM_ROWS * DEF_NUM_COLS) / static_cast<float>(numAliensLeft + 1)))) == 1;
}

bool AlienSwarm::getAlienToShootBomb(Alien& alien) {
	std::vector<int> active_cols;
	std::vector<Alien> aliens_bottom;

	// Look for columns with alive aliens
	for (int col{ 0 }; col < DEF_NUM_COLS; col++) {
		for (int row{ 0 }; row < DEF_NUM_ROWS; row++) {
			if (aliens.at(row).at(col).getAlienState() == Alien_State::AS_ALIVE) {
				active_cols.push_back(col);
				break;
			}
		}
	}

	// Get bottom aliens of each active column
	for (const auto& col : active_cols) {
		for (int row{ DEF_NUM_ROWS - 1 }; row >= 0; row--) {
			if (aliens.at(row).at(col).getAlienState() == Alien_State::AS_ALIVE) {
				aliens_bottom.push_back(aliens.at(row).at(col));
				break;
			}
		}
	}

	if (!aliens_bottom.empty()) {
		// Return randomly an alien
		alien = aliens_bottom.at(rand() % aliens_bottom.size());
		return true;
	}
	else {
		return false;
	}
}

void AlienSwarm::shootBomb(const Alien& alien) {
	int bomb_id{ 0 };
	for (int i{ 0 }; i < bombs.size(); i++) {
		if (bombs.at(i).getPosition().x == DEF_NOT_IN_PLAY || bombs.at(i).getPosition().y == DEF_NOT_IN_PLAY) {
			bomb_id = i;
			break;
		}
	}
	isShootingBomb = true;
	bombs.at(bomb_id).setPosition(alien.getPosition().x + 1, alien.getPosition().y + alien.getSpriteSize().height); // x = middle of the alien, y = bottom of the alien
	numBombsInPlay++;
}

void AlienSwarm::moveChangeAnimationBombs(const Game& game) {
	for (auto& bomb : bombs) {
		if (bomb.getPosition().y != DEF_NOT_IN_PLAY || bomb.getPosition().x != DEF_NOT_IN_PLAY)
		{
			if (!isShootingBomb) {
				bomb.setPosition(bomb.getPosition().x, bomb.getPosition().y + bomb.getSpeed());
				bomb.updateAnimation();
				bomb.setSpriteDependingOnAnimation();
			}
			else {
				isShootingBomb = false;
			}
			if (bomb.getPosition().y >= game.getWindowSize().height) {
				bomb.reset();
				numBombsInPlay--;
			}
		}
	}
}

void AlienSwarm::reset(const Game& game) {
	AlienSwarm alien_swarm_new(game);

	position = alien_swarm_new.position;
	aliens = alien_swarm_new.aliens;
	numAliensLeft = alien_swarm_new.numAliensLeft;
	directionRight = alien_swarm_new.directionRight;
	movementTimer = alien_swarm_new.movementTimer;
	line = alien_swarm_new.line;
	bombs = alien_swarm_new.bombs;
	numBombsInPlay = alien_swarm_new.numBombsInPlay;
	isShootingBomb = alien_swarm_new.isShootingBomb;
}