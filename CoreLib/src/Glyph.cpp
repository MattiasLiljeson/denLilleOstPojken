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

void Glyph::setRect(Rect p_rect)
{
	if (m_spriteInfo)
		m_spriteInfo->textureRect = p_rect;
}

void Glyph::setVisibility(bool p_set)
{
	if (m_spriteInfo)
		m_spriteInfo->visible = p_set; 
}