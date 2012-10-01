#include "SpeedPill.h"

SpeedPill::SpeedPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats): Collectable(p_spriteInfo, p_gameStats)
{
	if (p_spriteInfo)
	{
		TilePosition t = p_tile->getTilePosition();
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		p_spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
		p_spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
		p_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.4f;
		p_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.4f;
	}
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