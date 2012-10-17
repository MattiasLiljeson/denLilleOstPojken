#include "Glyph.h"

Glyph::Glyph(SpriteInfo* p_spriteInfo) : GameObject(p_spriteInfo)
{

}

Glyph::~Glyph()
{

}

void Glyph::update(float p_deltaTime, InputInfo p_inputInfo)
{

}

int Glyph::setRect(Rect p_rect)
{
	if(m_spriteInfo != NULL)
	{
		m_spriteInfo->textureRect = p_rect;
		return GAME_OK;
	}
	else
	{
		return GAME_FAIL;
	}
}

int Glyph::setVisibility(bool p_set)
{
	if(m_spriteInfo != NULL)
	{
		m_spriteInfo->visible = p_set;
		return GAME_OK;
	}
	else
	{
		return GAME_FAIL;
	}
}