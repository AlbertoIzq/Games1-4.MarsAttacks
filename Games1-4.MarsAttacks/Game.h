#pragma once

#include "Other.h" // // Needed for Position and Size, for "windows.h" and setConsoleWindowSize()

enum class Game_State
{
	GS_INTRO = 0,
	GS_INSTRUCTIONS_1,
	GS_INSTRUCTIONS_2,
	GS_PLAY, // Main status
 	GS_PLAYER_DEAD, // When player gets hits and dies
	GS_WAIT, // Game waits while player revives; Game waits before going to the next level
	//GS_PAUSE, // TODO
	GS_GAME_OVER,
	GS_HIGH_SCORES
};

class Game
{
public:
	static const Size DEF_WINDOW_SIZE; // Initialized in .cpp
	static constexpr int DEF_WAIT_TIMER{ 30 };
	static constexpr int DEF_LEVEL_MAX{ 10 };
private:
	static constexpr int DEF_WINDOW_WIDTH{ 80 };
	static constexpr int DEF_WINDOW_HEIGHT{ 40 };
	static constexpr int DEF_WINDOW_WIDTH_PIXELS{ 526 }; // Values obtained by setting console size manually when running the program to have DEF_WINDOW size in pixels, get the value in setConsoleWindowSize
	static constexpr int DEF_WINDOW_HEIGHT_PIXELS{ 614 };
	static constexpr Game_State DEF_GAME_STATE{ Game_State::GS_INTRO };
	static constexpr int DEF_LEVEL{ 1 };

protected:
	Size windowSize;
	Game_State currentState;
	int level;
	int waitTimer; // Timer to wait when player gets hit or game goes to next level

	int playerNameHPositionCursor;
	std::vector<int> playerNameVPositionCursor; // To store in each letter where we were
	std::string playerName;
public:
	Game();

	// GET METHODS
	inline Size getWindowSize() const { return windowSize; }
	inline Game_State getCurrentState() const { return currentState; }
	inline int getLevel() const { return level; }
	inline int getWaitTimer() const { return waitTimer; }
	inline std::string getPlayerName() const { return playerName; }

	// SET METHODS
	inline void setCurrentState(Game_State state) { currentState = state; }
	inline void setLevel(int level) { this->level = level; }
	inline void setWaitTimer(int wait_timer) { waitTimer = wait_timer; }
	
	void setConsoleWindowSize(); // Sets window size to default values
	void resetLevel();
	void resetAll();

	void drawPlayerName(const int& pos_x, const int& pos_y) const;
	void moveNameLetterRight();
	void moveNameLetterLeft();
	void moveNameLetterUp();
	void moveNameLetterDown();
};