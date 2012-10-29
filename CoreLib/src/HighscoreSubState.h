#ifndef HIGHSCORESUBSTATE_H
#define HIGHSCORESUBSTATE_H


//#include "DebugPrint.h"
#include "ToString.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "MenuSubState.h"

class MenuSubStateManager;

using namespace std;

struct HighScoreItem
{
	int score;
	bool operator<(const HighScoreItem& p_other)
	{
		return score > p_other.score;
	}
};

class HighscoreSubState : public MenuSubState
{
private:
	vector<HighScoreItem> m_highscore;

public:
	enum { HS_MAIN, HS_NUM_ITEMS };
	HighscoreSubState( MenuSubStateManager* p_manager );
	~HighscoreSubState();

	void readHighScore();
	//void updateHighScore();
	void writeHighScore();

	virtual void selectBtn();

	virtual void onEntry();
	virtual void onExit();
};

#endif // HIGHSCORESUBSTATE_H
