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
	MenuItem* m_itemPowerUp;
	MenuItem* m_buffPowerUp;
	SpriteInfo* m_speedIcon;
public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_speedIcon);
	virtual ~GUI();
	void update(float p_dt);
};

#endif