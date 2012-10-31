#ifndef GOFACTORY_H
#define GOFACTORY_H

#include "Avatar.h"
#include "Glyph.h"
#include "IODevice.h"
#include "MenuItem.h"
#include "Rat.h"
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
#include "BombPill.h"
#include "Bomb.h"
#include "TMFactory.h"
#include "WallSwitch.h"
#include "TileTypes.h"
#include "GlyphAnimIn.h"
#include "GlyphAnimOut.h"
#include "InfectedRat.h"
#include <string>

// forward declarations
class Glyph;
class GlyphMap;
class TextArea;
class MenuItem;

class GOFactory
{
private:
	IODevice*	m_io;
	TMFactory*	m_tileMapFactory;
private:
	fVector3 GetCenter(Tile* p_tile, float p_depth);
	fVector2 GetScaledSize(Tile* p_tile, float p_scale);
public:
	GOFactory(IODevice* p_io);
	~GOFactory();

	// Mattias: Why private?
	SoundInfo*	CreateSoundInfo(string p_sound, int p_volume);

	Avatar*		CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats);
	Monster*	CreateMonster(Tile* p_tile, Tilemap* p_map, GameStats* p_stats, int p_type);
	Trap*		CreateTrap(Tile* p_tile, Tilemap* p_map);

	SuperPill*	CreateSuperPill(Tile* p_tile, GameStats* p_gameStats);
	SpeedPill*	CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats);
	BombPill*	CreateBombPill(Tile* p_tile, GameStats* p_gameStats);
	Bomb*		CreateBomb(Tile* p_tile, Tilemap* p_map);
	Pill*		CreatePill(Tile* p_tile, GameStats* p_gameStats);

	Tilemap*	CreateTileMap(int p_theme, int p_width, int p_height, vector<int> p_mapData);
	Tile*		CreateTile(bool p_type, TilePosition p_position, float p_width,
				float p_height);

	Switch*		CreateSwitch(Tile* p_tile, GameStats* p_gameStats,
				vector<WallSwitch*> p_targets, int p_type);
	
	WallSwitch* CreateWallSwitch(Tile* p_tile, int p_type);

	MenuItem* createMenuItem( fVector3 p_position, fVector2 p_size,
		string p_text="", fVector2 p_textOffset=fVector2(),
		fVector2 p_fontSize=fVector2(), string p_bgTexPath="" );

	TextArea* createMenuItemTextArea( fVector3 p_position,
	string p_text, fVector2 p_textOffset, fVector2 p_fontSize );

	Glyph*		CreateGlyph(const string& p_texture, float p_x, float p_y,
					fVector2 p_size,
					vector<GlyphAnimation*> p_animations = vector<GlyphAnimation*>());

	GUI*		CreateGUI(GameStats* p_gameStats);

	SpriteInfo*	CreateSpriteInfo(string p_texture, fVector3 p_position,
				fVector2 p_size, Rect* p_sourceRect);

};

#endif