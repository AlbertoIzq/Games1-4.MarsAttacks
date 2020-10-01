#pragma once

#include "Other.h" // // Needed for Position and Size, for "windows.h" and setConsoleWindowSize()

// Needed for Position and Size

enum class Game_State
{
	GS_INTRO = 0,
	GS_HIGH_SCORES,
	GS_PLAY,
	GS_PLAYER_DEAD,
	GS_WAIT,
	GS_GAME_OVER
};

class Game
{
public:
	static const Size DEF_WINDOW_SIZE; // Initialized in .cpp
private:
	static const int DEF_WINDOW_WIDTH{ 80 };
	static const int DEF_WINDOW_HEIGHT{ 40 };
	static const int DEF_WINDOW_WIDTH_PIXELS{ 526 }; // Values obtained by setting console size manually when running the program to have DEF_WINDOW size in pixels, get the value in setConsoleWindowSize
	static const int DEF_WINDOW_HEIGHT_PIXELS{ 614 };
	static constexpr Game_State DEF_GAME_STATE{ Game_State::GS_PLAY }; // for now - TODO: Change to GS_INTRO
	static constexpr int DEF_LEVEL{ 1 };
protected:
	Size windowSize;
	Game_State currentState;
	int level;
public:
	Game();

	// GET METHODS
	inline Size getSize() const { return windowSize; }
	inline int getLevel() const { return level; }

	// SET METHODS
	inline void setLevel(int level) { this->level = level; }

	void setConsoleWindowSize(); // Sets window size to default values
};