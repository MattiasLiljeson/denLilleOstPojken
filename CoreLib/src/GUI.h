#ifndef GUI_H
#define GUI_H

#include "GameStats.h"
#include <SpriteInfo.h>

class MenuItem;

struct VictoryStruct
{
	MenuItem* victory;
	MenuItem* baseScore;
	MenuItem* multiplier;
	MenuItem* finalScore;
};

class GUI
{
private:
	GameStats* m_stats;
	vector<SpriteInfo*> m_lives;
	MenuItem* m_elapsedTime;
	MenuItem* m_parTime;
	MenuItem* m_score;
	MenuItem* m_totalScore;
	MenuItem* m_itemPowerUp;
	MenuItem* m_buffPowerUp;
	SpriteInfo* m_speedIcon;
	SpriteInfo* m_bombIcon;

	//Result texts
	VictoryStruct m_victoryData;

public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, MenuItem* p_parTime, MenuItem* p_totalScore, 
		VictoryStruct p_victory, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_speedIcon, SpriteInfo* p_bombIcon);
	virtual ~GUI();
	void update(float p_dt);

	void showVictory();
	void showBaseScore(int p_score);
	void showMultiplier(float p_multiplier);
	void showTotalScore(int p_finalScore);
};

#endif