#include "Alien.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position Alien::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Alien::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Alien::DEF_SPRITE_30P_1{ "/oo\\", "<  >" };
const std::vector<std::string> Alien::DEF_SPRITE_30P_2{ "/oo\\", "</\"\"\\>" };
const std::vector<std::string> Alien::DEF_SPRITE_20P_1{ " >< ", "|\\/|" };
const std::vector<std::string> Alien::DEF_SPRITE_20P_2{ "|><|", "/  \\" };
const std::vector<std::string> Alien::DEF_SPRITE_10P_1{ "/--\\", "/  \\" };
const std::vector<std::string> Alien::DEF_SPRITE_10P_2{ "/--\\", "<  >" };

Alien::Alien()
	: StaticObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE_10P_1 }, alienState{ Alien_State::AS_ALIVE }, alienType{ Alien_Type::AT_10P } {
}