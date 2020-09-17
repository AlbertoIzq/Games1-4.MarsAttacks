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

class Game
{
private:
	static constexpr Game_State DEF_GAME_STATE = Game_State::GS_PLAY;
	static constexpr int DEF_LEVEL = 1;
protected:
	//Size windowSize;
	Game_State currentState;
	int level;
public:
	Game();

	void setConsoleWindowSize();
};

