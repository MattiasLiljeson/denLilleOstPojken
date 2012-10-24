#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"
#include "Tilemap.h"
#include "Monster.h"
#include "Animation.h"

class Flame
{
private:
	SpriteInfo* m_spriteInfo;
	float		m_dt;
	Animation*	m_animation;
	Tile*		m_tile;
public:
	Flame(SpriteInfo* p_spriteInfo, Tile* p_tile)
	{
		m_spriteInfo = p_spriteInfo;
		m_spriteInfo->visible = true;
		m_dt = 0;
		m_animation = new Animation(fVector2(0, 0), 64, 64, 5, 0.15f);
		m_tile = p_tile;
	}
	virtual ~Flame()
	{
		delete m_animation;
	}
	void update(float p_elapsedTime)
	{
		m_animation->update(p_elapsedTime);
		m_spriteInfo->textureRect = m_animation->getCurrentFrame();
	}
	bool isDead()
	{
		return m_animation->hasFinished();
	}
	Tile* getTile()
	{
		return m_tile;
	}
};

//Class that handles a bomb
//A bomb is an item that can be 
//placed by the avatar and will explode
class Bomb: public GameObject
{
private:
	vector<pair<Tile*, SpriteInfo*> > m_flameSpawn;
	vector<Flame*> m_flames;
	float m_elapsedTime;
	int m_currentDist;
	Tile* m_start;
public:
	Bomb(vector<pair<Tile*, SpriteInfo*> > p_flames, Tile* p_tile, Tilemap* p_map);
	virtual ~Bomb();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	bool	isColliding(Monster* p_monster);
};

#endif
