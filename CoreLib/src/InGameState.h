#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State.h"
#include "GameStats.h"
#include "MapHeader.h"
#include "HighScore.h"

class InGameState: public State
{
private:
	IODevice*				m_io;
	vector<GameObject*>		m_gameObjects;
	Avatar*					m_avatar;
	vector<Monster*>		m_monsters;
	vector<Trap*>			m_traps;
	vector<Bomb*>			m_bombs;
	GOFactory*				m_factory;
	GUI*					m_gui;

	Tilemap*				m_tileMap;
	GameStats*				m_stats;
	vector<MapData>			m_maps;
	int						m_currentMap;
	Tile*					m_startTile;
	float					m_defeatTime;
	float					m_victoryTime;
	float					m_toneOutTimer;
	int						m_desiredMap;

	bool					m_paused;

	//Music
	SoundInfo* m_backgroundMusic;

private:
	void updateOnVictory(float p_dt, InputInfo p_input);
	void updateOnDefeat(float p_dt, InputInfo p_input);
public:
	InGameState(StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps,
		bool p_reset = false);
	virtual ~InGameState();
	void update(float p_dt);
	void handleInput(InputInfo p_input);
	void draw(float p_dt);
	void checkAndResolveDynamicCollision();
	void checkAndResolveStaticCollision();
	//Flag to indicate if restart was called when completing a level
	void restart();
	int setCurrentMap( MapData p_map );
	int setCurrentMap( int p_mapIdx );
	bool onEntry();
	bool onExit();
};

#endif
