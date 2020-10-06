#include "Score.h"

Score::Score()
	: score{ 0 } {
    // name initialization
    for (int i{ 0 }; i < DEF_MAX_CHAR_NAME_SCORE; i++) {
        name += 'A';
    }
}