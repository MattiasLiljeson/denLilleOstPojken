#include "SuperPill.h"


SuperPill::SuperPill(IODevice* p_io, Tile* p_tile, GameStats* p_gameStats): Collectable(NULL,p_gameStats)
{
	if(p_io)
	{
		m_spriteInfo = new SpriteInfo();
		TilePosition t = p_tile->getTilePosition();
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		m_spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.2f;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.7f;
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.7f;
		m_spriteInfo->textureFilePath = "..\\Textures\\SuperPill.png";
		p_io->addSpriteInfo(m_spriteInfo);
	}
	m_tile = p_tile;
	m_tile->addPill(this);
	m_consumed = false;
}

SuperPill::~SuperPill()
{

}

void SuperPill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if(m_consumed)
	{
		m_spriteInfo->visible = false;
	}
}

void SuperPill::consume()
{
	if(!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->setSuperMode();
	}
}