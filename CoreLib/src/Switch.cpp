#include "Switch.h"

Switch::Switch(IODevice* p_io, Tile* p_tile, Tilemap* p_map, GameStats* p_gameStats): Collectable(NULL, p_gameStats)
{
	m_map = p_map;
	m_targets.push_back(TilePosition(4, 2));
	m_targets.push_back(TilePosition(5, 2));
	if (p_io)
	{
		m_spriteInfo = new SpriteInfo();
		TilePosition t = p_tile->getTilePosition();
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		m_spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.7f;
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.7f;
		m_spriteInfo->textureFilePath = "..\\Textures\\button.png";
		p_io->addSpriteInfo(m_spriteInfo);
	}
	

	m_tile = p_tile;
	m_tile->addPill(this);
	m_eaten = false;
}
void Switch::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_eaten)
	{
		m_spriteInfo->visible = false;
	}
}
void Switch::consume()
{
	if (!m_eaten)
	{
		m_eaten = true;
		m_tile = NULL;
		for (int i = 0; i < m_targets.size(); i++)
		{
			Tile* t = m_map->getTile(m_targets[i]);
			t->switchState();
		}
	}
}