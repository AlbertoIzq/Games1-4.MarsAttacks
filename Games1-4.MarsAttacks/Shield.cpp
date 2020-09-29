#include "Shield.h"

// Initialization of class structs default values (They cannot be initialized in .h)
const Position Shield::DEF_INI_POSITION{ DEF_INI_POSITION_X , DEF_INI_POSITION_Y };
const Size Shield::DEF_SPRITE_SIZE{ DEF_SPRITE_WIDTH, DEF_SPRITE_HEIGHT };
const std::vector<std::string> Shield::DEF_SPRITE{ "/IIIII\\", "IIIIIII", "I/   \\I" };

Shield::Shield()
	: StaticObject{ DEF_INI_POSITION, DEF_SPRITE_SIZE, DEF_SPRITE } {
}