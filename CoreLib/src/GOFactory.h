#ifndef GOFACTORY_H
#define GOFACTORY_H

#include "Avatar.h"
#include "Glyph.h"
#include "IODevice.h"
#include "MenuItem.h"
#include "Monster.h"
#include "Pill.h"
#include "SpeedPill.h"
#include "SuperPill.h"
#include "Switch.h"
#include "Glyph.h"
#include "Trap.h"
#include <SoundInfo.h>
#include "GUI.h"
#include "TextArea.h"
#include "Tilemap.h"
#include <SoundInfo.h>
#include <fVector2.h>
#include <fVector3.h>

// forward declarations
class Glyph;
class GlyphMap;
class TextArea;
class MenuItem;

class GOFactory
{
private:
	IODevice* m_io;

private:
	SpriteInfo* CreateSpriteInfo(string p_texture, fVector3 p_position,
		fVector2 p_size, Rect* p_sourceRect);

	fVector3 GetCenter(Tile* p_tile, float p_depth);
	fVector2 GetScaledSize(Tile* p_tile, float p_scale);
public:
	GOFactory(IODevice* p_io);

	// Mattias: Why private?
	SoundInfo*	CreateSoundInfo(string p_sound, int p_volume);

	Avatar* CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats);
	Monster* CreateMonster(Tile* p_tile, Tilemap* p_map);
	Trap* CreateTrap(Tile* p_tile, Tilemap* p_map);

	SuperPill* CreateSuperPill(Tile* p_tile, GameStats* p_gameStats);
	SpeedPill* CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats);
	Pill* CreatePill(Tile* p_tile, GameStats* p_gameStats);

	Tilemap* CreateTileMap(int p_width, int p_height, bool* p_initData);
	Tile* CreateTile(bool p_type, TilePosition p_position, float p_width,
		float p_height);

	Switch* CreateSwitch(Tile* p_tile, Tilemap* p_map, GameStats* p_gameStats,
		vector<TilePosition> p_targets);

	MenuItem* createMenuItem( fVector3 p_position, fVector2 p_size,
		string p_text="", fVector2 p_textOffset=fVector2(),
		fVector2 p_fontSize=fVector2(), string p_bgTexPath="" );

	Glyph* CreateGlyph(const string& p_texture, 
					   float p_x, float p_y, fVector2 p_size);

	GUI* CreateGUI(GameStats* p_gameStats);
};

#endif