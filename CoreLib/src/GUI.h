#ifndef GUI_H
#define GUI_H

#include "GameStats.h"
#include <SpriteInfo.h>
#include <string>

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
struct ContinueStruct
{
	MenuItem*	pressToContinue;
	MenuItem*	pressToEnd;
};
struct DefeatStruct
{
	MenuItem* defeated;
	MenuItem* cost;
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

	// Shake score item when picking up score.
	int m_lastIterationScore;
	float m_scoreShakeAccumulated;
	float m_scoreShakeDecayFactor;
	float m_scoreShakeMult;

	// Shake elapsed time when close to par time
	float m_timeShakeTime;
	float m_timeShakeMult;

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

	//Continue texts
	ContinueStruct m_continue;

public:
	GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, MenuItem* p_parTime, MenuItem* p_totalScore, 
		VictoryStruct p_victory, PauseStruct p_pauseData, DefeatStruct p_defeatData, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_buffSlot, 
		SpriteInfo* p_itemSlot,	SpriteInfo* p_bombIcon, SpriteInfo* p_speedIcon, ContinueStruct p_continue);
	virtual ~GUI();
	void update(float p_dt, InputInfo p_input);

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

	//Information texts
	void showContinue();
	void showEnd();
};

#endif