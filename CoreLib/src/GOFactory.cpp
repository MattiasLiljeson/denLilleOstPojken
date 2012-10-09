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
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/pacman-1974_sheet.png", pos, size, &r);
	return new Avatar(spriteInfo, p_map, p_startTile, p_stats);
}
Monster* GOFactory::CreateMonster(Tile* p_tile, Tilemap* p_map)
{
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	TilePosition tp = p_tile->getTilePosition();

	fVector3 pos = fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, 0.2f);
	fVector2 size = fVector2(w * 0.9f, h * 0.9f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("..\\Textures\\SeaMonster.png", pos, size, NULL);
	return new Monster(spriteInfo, p_tile, p_map);
}
SuperPill* GOFactory::CreateSuperPill(Tile* p_tile, GameStats* p_gameStats)
{
	SpriteInfo* spriteInfo = new SpriteInfo();
	TilePosition t = p_tile->getTilePosition();
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.2f;
	spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.7f;
	spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.7f;
	spriteInfo->textureFilePath = "..\\Textures\\SuperPill.png";
	m_io->addSpriteInfo(spriteInfo);
	return new SuperPill(spriteInfo, p_tile, p_gameStats);
}
SpeedPill* GOFactory::CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats)
{
	SpriteInfo* spriteInfo = new SpriteInfo();
	TilePosition t = p_tile->getTilePosition();
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.1f;
	spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.7f;
	spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.7f;
	spriteInfo->textureFilePath = "..\\Textures\\drug.png";
	m_io->addSpriteInfo(spriteInfo);
	return new SpeedPill(spriteInfo, p_tile, p_gameStats);
}
Pill* GOFactory::CreatePill(Tile* p_tile, GameStats* p_gameStats)
{
	SpriteInfo* spriteInfo = new SpriteInfo();
	TilePosition t = p_tile->getTilePosition();
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
	spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.1f;
	spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.5f;
	spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.5f;
	spriteInfo->textureFilePath = "..\\Textures\\pill.png";
	m_io->addSpriteInfo(spriteInfo);
	return new Pill(spriteInfo, p_tile, p_gameStats);
}


SpriteInfo* GOFactory::CreateSpriteInfo(string p_texture, fVector3 p_position, fVector2 p_size, Rect* p_sourceRect)
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