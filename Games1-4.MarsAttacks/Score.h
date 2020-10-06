#pragma once

#include <string>

class Score
{
public:
	static constexpr int DEF_MAX_CHAR_NAME_SCORE{ 5 };
protected:
	int score;
	std::string name;
public:
	Score();

	// GET METHODS
	inline int getScore() const { return score; }
	inline std::string getName() const { return name; }

	// SET METHODS
	void setScore(const int& score) { this->score = score; }
	void setName(const std::string& name) { this->name = name; }
};

