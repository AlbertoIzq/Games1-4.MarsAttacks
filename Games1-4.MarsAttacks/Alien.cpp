#include "Alien.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position Alien::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Alien::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Alien::DEF_SPRITE_30P_1{ "/oo\\", "<  >" };
const std::vector<std::string> Alien::DEF_SPRITE_30P_2{ "/oo\\", "<\"\"\>" };
const std::vector<std::string> Alien::DEF_SPRITE_20P_1{ " >< ", "|\\/|" };
const std::vector<std::string> Alien::DEF_SPRITE_20P_2{ "|><|", "/  \\" };
const std::vector<std::string> Alien::DEF_SPRITE_10P_1{ "/--\\", "/  \\" };
const std::vector<std::string> Alien::DEF_SPRITE_10P_2{ "/--\\", "<  >" };
const std::vector<std::string> Alien::DEF_SPRITE_EXPLOSION{ "\\||/", "/||\\" };

Alien::Alien()
	: StaticObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE_10P_1 }, alienState{ Alien_State::AS_ALIVE },
	alienType{ Alien_Type::AT_10P }, explosionTimer{ DEF_NOT_IN_PLAY }, animation{ DEF_ANIMATION } {
}

void Alien::draw() const {
	if (alienState != Alien_State::AS_DEAD) {
		drawSprite(position.x, position.y, sprite);
	}
}

void Alien::setSpriteDependingOnState() {
	switch (alienState)
	{
	case Alien_State::AS_ALIVE:
		if (animation == 1) {
			switch (alienType)
			{
			case Alien_Type::AT_10P:
				sprite = DEF_SPRITE_10P_1;
				break;
			case Alien_Type::AT_20P:
				sprite = DEF_SPRITE_20P_1;
				break;
			case Alien_Type::AT_30P:
				sprite = DEF_SPRITE_30P_1;
				break;
			}
		}
		else { // animation == 2
			switch (alienType)
			{
			case Alien_Type::AT_10P:
				sprite = DEF_SPRITE_10P_2;
				break;
			case Alien_Type::AT_20P:
				sprite = DEF_SPRITE_20P_2;
				break;
			case Alien_Type::AT_30P:
				sprite = DEF_SPRITE_30P_2;
				break;
			}
		}
		break;
	case Alien_State::AS_DEAD:
		break;
	case Alien_State::AS_EXPLODING:
		sprite = DEF_SPRITE_EXPLOSION;
		break;
	default:
		break;
	}
}

void Alien::updateExplosion() {
	if (explosionTimer >= 0) {
		explosionTimer--;
	}
	else if (explosionTimer < 0 && alienState == Alien_State::AS_EXPLODING) {
		explosionTimer = DEF_NOT_IN_PLAY;
		alienState = Alien_State::AS_DEAD;
	}
}

