#ifndef GUI_H
#define GUI_H

#include "GameStats.h"
#include <SpriteInfo.h>

class MenuItem;

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
public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, MenuItem* p_parTime, MenuItem* p_totalScore, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_speedIcon, SpriteInfo* p_bombIcon);
	virtual ~GUI();
	void update(float p_dt);
};

#endif