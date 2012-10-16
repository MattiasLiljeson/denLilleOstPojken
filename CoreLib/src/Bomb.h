#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"
#include "Tilemap.h"
#include "Monster.h"

class Bomb: public GameObject
{
private:
	vector<pair<Tile*, SpriteInfo*>> m_flames;
	float m_elapsedTime;
	int m_currentDist;
	Tile* m_start;
public:
	Bomb(vector<pair<Tile*, SpriteInfo*>> p_flames, Tile* p_tile, Tilemap* p_map);
	virtual ~Bomb();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	bool	isColliding(Monster* p_monster);
};

#endif