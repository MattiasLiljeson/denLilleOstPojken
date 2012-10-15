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
	m_spriteInfo->textureRect = p_rect;
}

void Glyph::setVisibility(bool p_set)
{
	m_spriteInfo->visible = p_set; 
}