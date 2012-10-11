#include "GOFactory.h"

GOFactory::GOFactory(IODevice* p_io)
{
	m_io = p_io;
}
Avatar* GOFactory::CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats)
{
	TilePosition tp = p_startTile->getTilePosition();
	float w = p_startTile->getWidth();
	float h = p_startTile->getHeight();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.5f);
	fVector2 size = fVector2(w * 0.6f, h * 0.6f);

	Rect r;
	r.x		= 385;
	r.y		= 0;
	r.width = 385;
	r.height = 450;
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/pacman-1974_sheet.png",
		pos, size, &r);
	return new Avatar(spriteInfo, p_map, p_startTile, p_stats);
}
Monster* GOFactory::CreateMonster(Tile* p_tile, Tilemap* p_map)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.2f);
	fVector2 size = fVector2(w * 0.9f, h * 0.9f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SeaMonster.png",
		pos, size, NULL);
	return new Monster(spriteInfo, p_tile, p_map);
}
SuperPill* GOFactory::CreateSuperPill(Tile* p_tile, GameStats* p_gameStats)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.2f);
	fVector2 size = fVector2(w * 0.7f, h * 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SuperPill.png",
		pos, size, NULL);
	return new SuperPill(spriteInfo, p_tile, p_gameStats);
}
SpeedPill* GOFactory::CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.1f);
	fVector2 size = fVector2(w * 0.7f, h * 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/drug.png",
		pos, size, NULL);
	return new SpeedPill(spriteInfo, p_tile, p_gameStats);
}
Pill* GOFactory::CreatePill(Tile* p_tile, GameStats* p_gameStats)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.1f);
	fVector2 size = fVector2(w * 0.5f, h * 0.5f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/pill.png",
		pos, size, NULL);
	return new Pill(spriteInfo, p_tile, p_gameStats);
}

Tilemap* GOFactory::CreateTileMap(int p_width, int p_height, bool* p_initData)
{
	float tileSizeX = m_io->getScreenWidth() / (float)p_width;
	float tileSizeY = m_io->getScreenHeight() / (float)p_height;
	Tile** tiles = new Tile*[p_width * p_height];
	for (int row = 0; row < p_height; row++)
	{
		for (int col = 0; col < p_width; col++)
		{
			tiles[row * p_width + col] = CreateTile(p_initData[row * p_width + col],
				TilePosition(col, row), tileSizeX, tileSizeY);
		}
	}
	return new Tilemap(p_width, p_height, tiles);
}
Tile* GOFactory::CreateTile(bool p_type, TilePosition p_position, float p_width,
	float p_height)
{
	fVector3 pos = fVector3(p_position.x * p_width + p_width * 0.5f,
		p_position.y * p_height + p_height * 0.5f, 0.0f);
	fVector2 size = fVector2(p_width, p_height);
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/wall.png",
		pos, size, NULL);
	spriteInfo->visible = !p_type;

	return new Tile(p_type, p_position, p_width, p_height, spriteInfo);
}
Switch* GOFactory::CreateSwitch(Tile* p_tile, Tilemap* p_map,
	GameStats* p_gameStats, vector<TilePosition> p_targets)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.2f);
	fVector2 size = fVector2(w * 0.7f, h * 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Red_button.png",
		pos, size, NULL);
	return new Switch(spriteInfo, p_tile, p_map, p_gameStats, p_targets);
}

SpriteInfo* GOFactory::CreateSpriteInfo(string p_texture, fVector3 p_position,
	fVector2 p_size, Rect* p_sourceRect)
{
	SpriteInfo* spriteInfo = new SpriteInfo;
	spriteInfo->transformInfo.translation[TransformInfo::X] = p_position.x;
	spriteInfo->transformInfo.translation[TransformInfo::Y] = p_position.y;
	spriteInfo->transformInfo.translation[TransformInfo::Z] = p_position.z;
	spriteInfo->transformInfo.scale[TransformInfo::X] = p_size.x;
	spriteInfo->transformInfo.scale[TransformInfo::Y] = p_size.y;
	spriteInfo->textureFilePath = p_texture;

	m_io->addSpriteInfo(spriteInfo);
	if (p_sourceRect)
	{
		spriteInfo->textureRect.x		= p_sourceRect->x;
		spriteInfo->textureRect.y		= p_sourceRect->y;
		spriteInfo->textureRect.width = p_sourceRect->width;
		spriteInfo->textureRect.height = p_sourceRect->height;
	}
	return spriteInfo;
}

MenuItem* GOFactory::createMenuItem()
{
	fVector3 pos = fVector3(400.0f, 400.0f, 0.99f);
	fVector2 size = fVector2(800.0f, 350.0f);
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SplashScreen.png",
		pos, size, NULL);
	return new MenuItem(spriteInfo);
}