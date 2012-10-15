#ifndef GUI_H
#define GUI_H

#include "GameStats.h"
#include <SpriteInfo.h>

class GUI
{
private:
	GameStats* m_stats;
	vector<SpriteInfo*> m_lives;
public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives);
	virtual ~GUI();
	void update(float p_dt);
};

#endif