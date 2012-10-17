#ifndef AVATARWALKING_H
#define AVATARWALKING_H

#include "GOState.h"
#include "Avatar.h"

class AvatarWalking : public GOState
{
private:
	NavigationData* m_navigationData;

	/*Tile* m_nextTile;
	Tile* m_queuedTile;
	Tilemap* m_map;

	int m_direction;
	int m_desired;*/

	GameStats* m_gameStats;

	//float dt;
private:
	void checkInput(InputInfo p_inputInfo);
	bool check180();
public:
	AvatarWalking(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats);
	virtual ~AvatarWalking();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif