#pragma once

#include "StaticObject.h"

enum class Alien_State {
	AS_ALIVE = 0,
	AS_DEAD,
	AS_EXPLODING
};

enum class Alien_Type {
	AT_30P = 0,
	AT_20P,
	AT_10P
};

class Alien : public StaticObject{
private:
	static const Position DEF_INI_POSITION; // Initialized in .cpp
	static constexpr int DEF_INI_POSITION_X{ DEF_NOT_IN_PLAY };
	static constexpr int DEF_INI_POSITION_Y{ DEF_NOT_IN_PLAY };
	static const Size DEF_SPRITE_SIZE; // Initialized in .cpp
public:
	static constexpr int DEF_SPRITE_WIDTH{ 4 };
	static constexpr int DEF_SPRITE_HEIGHT{ 2 };
	static const std::vector<std::string> DEF_SPRITE_30P_1; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_30P_2; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_20P_1; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_20P_2; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_10P_1; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_10P_2; // Initialized in .cpp
	static const std::vector<std::string> DEF_SPRITE_EXPLOSION; // Initialized in .cpp
	static constexpr int DEF_EXPLOSION_TIME{ 4 };
protected:
	Alien_State alienState;
	Alien_Type alienType;
	int explosionTimer; // This is going to capture how long to explode for
public:
	Alien();
	virtual ~Alien() = default;

	void setSpriteDependingOnState();
	virtual void draw() const override;

	// GET METHODS
	inline Alien_State getAlienState() const { return alienState; }
	inline Alien_Type getAlienType() const { return alienType; }
	inline int getExplosionTimer() const { return explosionTimer; }

	// SET METHODS
	inline void setAlienState(const Alien_State alien_state) { alienState = alien_state; }
	inline void setAlienType(const Alien_Type alien_type) { alienType = alien_type; }
	inline void setExplosionTimer(const int explosion_timer) { explosionTimer = explosion_timer; }
};