#include "Switch.h"

Switch::Switch(IODevice* p_io, Tile* p_tile, Tilemap* p_map, GameStats* p_gameStats, vector<TilePosition> p_targets): Collectable(NULL, p_gameStats)
{
	m_io = p_io;
	m_map = p_map;

	m_targets = p_targets;
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
		m_spriteInfo->textureFilePath = "../Textures/Red_button.png";
		p_io->addSpriteInfo(m_spriteInfo);
	}
	

	m_tile = p_tile;
	m_tile->addPill(this);
	m_consumed = false;
	m_cooldown = 0;
}
void Switch::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_cooldown == 0 && m_spriteInfo->textureFilePath == "../Textures/green_button.png")
	{
		m_spriteInfo->textureFilePath = "../Textures/Red_button.png";
		m_io->updateSpriteInfo(m_spriteInfo);
	}
	else if (m_cooldown > 0 && m_spriteInfo->textureFilePath == "../Textures/Red_button.png")
	{
		m_spriteInfo->textureFilePath = "../Textures/green_button.png";
		m_io->updateSpriteInfo(m_spriteInfo);
	}
	m_cooldown = max(m_cooldown - p_deltaTime, 0.0f);
}
void Switch::consume()
{
	if (m_cooldown <= 0)
	{
		for (int i = 0; i < m_targets.size(); i++)
		{
			Tile* t = m_map->getTile(m_targets[i]);
			t->switchState();
		}
		m_cooldown = 5;
	}
}