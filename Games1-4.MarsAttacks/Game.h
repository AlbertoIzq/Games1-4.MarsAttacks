#pragma once

enum class Game_State
{
	GS_INTRO = 0,
	GS_HIGH_SCORES,
	GS_PLAY,
	GS_PLAYER_DEAD,
	GS_WAIT,
	GS_GAME_OVER
};

struct Size {
	int width;
	int height;
};

class Game
{
private:
	Size windowSize;
	Game_State currentState;
	int level;
public:
	Game();

	void setConsoleWindowSize();
};

