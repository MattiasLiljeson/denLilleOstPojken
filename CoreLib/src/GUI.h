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
struct PauseStruct
{
	MenuItem* paused;
	MenuItem* pressToPlay;
};
struct DefeatStruct
{
	MenuItem* defeated;
	MenuItem* cost;
	MenuItem* cont;

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

	//Item/Buff-related
	MenuItem* m_itemPowerUp;
	MenuItem* m_buffPowerUp;
	SpriteInfo* m_buffSlot;
	SpriteInfo* m_itemSlot;
	SpriteInfo* m_speedBuff;
	SpriteInfo* m_bombItem;

	//Victory texts
	VictoryStruct m_victoryData;

	//Pause texts
	PauseStruct m_pauseData;

	//Defeat texts
	DefeatStruct m_defeatData;

public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, MenuItem* p_parTime, MenuItem* p_totalScore, 
		VictoryStruct p_victory, PauseStruct p_pauseData, DefeatStruct p_defeatData, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_buffSlot, 
		SpriteInfo* p_itemSlot,	SpriteInfo* p_bombIcon, SpriteInfo* p_speedIcon);
	virtual ~GUI();
	void update(float p_dt);

	void setSpecialVisible(Collectable* p_collectable, SpriteInfo* p_special);

	//Victory texts
	void showVictory();
	void showBaseScore(int p_score);
	void showMultiplier(float p_multiplier);
	void showTotalScore(int p_finalScore);

	//Pause texts
	void pause();
	void unpause();

	//Defeat texts
	void showDefeat();
	void showCost();
	void showContinue();
};

#endif