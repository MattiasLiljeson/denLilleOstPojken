#include "SpeedPill.h"

SpeedPill::SpeedPill(IODevice* p_io, Tile* p_tile, GameStats* p_gameStats): Collectable(NULL, p_gameStats)
{
	SpriteInfo spriteInfo;
	TilePosition t = p_tile->getTilePosition();
	float w = p_tile->getWidth();
	float h = p_tile->getHeight();
	spriteInfo.transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
	spriteInfo.transformInfo.scale[TransformInfo::X] = w * 0.7f;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = h * 0.7f;
	spriteInfo.textureFileName = "..\\Textures\\drug.png";
	m_spriteInfo = p_io->addSpriteInfo(spriteInfo);

	m_tile = p_tile;
	m_tile->addPill(this);
	m_eaten = false;
}
void SpeedPill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_eaten)
	{
		m_spriteInfo->visible = false;
	}
}
void SpeedPill::consume()
{
	if (!m_eaten)
	{
		m_eaten = true;
		m_tile = NULL;
		m_gameStats->setSpeeded();
	}
}