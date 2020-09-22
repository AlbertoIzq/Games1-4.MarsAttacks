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
	friend class Player; // To give access to DEF_WINDOW
private:
	static const Size DEF_WINDOW_SIZE; // Initialized in .cpp
	static const int DEF_WINDOW_WIDTH{ 64 };
	static const int DEF_WINDOW_HEIGHT{ 50 };
	static const int DEF_WINDOW_WIDTH_PIXELS{ 424 }; // Values obtained by setting console size manually when running the program to have DEF_WINDOW size and 
	static const int DEF_WINDOW_HEIGHT_PIXELS{ 758 };
	static constexpr Game_State DEF_GAME_STATE{ Game_State::GS_PLAY }; // for now - TODO: Change to GS_INTRO
	static constexpr int DEF_LEVEL{1};
protected:
	Size windowSize;
	Game_State currentState;
	int level;
public:
	Game();

	void setConsoleWindowSize(); // Sets window size to default values
};

