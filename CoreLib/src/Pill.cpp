#include "Pill.h"

Pill::Pill(IODevice* p_io, Tile* p_tile, GameStats* p_gameStats): Collectable(NULL, p_gameStats)
{
	p_gameStats->addPill();

	m_spriteInfo = new SpriteInfo();
	TilePosition t = p_tile->getTilePosition();
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	m_spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.1f;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.5f;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.5f;
	m_spriteInfo->textureFilePath = "..\\Textures\\pill.png";
	p_io->addSpriteInfo(m_spriteInfo);

	m_tile = p_tile;
	m_tile->addPill(this);
	m_consumed = false;
}
void Pill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_consumed)
	{
		m_spriteInfo->visible = false;
	}
}
void Pill::consume()
{
	if (!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->pillEaten();
	}
}