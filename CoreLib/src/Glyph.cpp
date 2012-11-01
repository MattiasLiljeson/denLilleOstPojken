#include "Glyph.h"

Glyph::Glyph( SpriteInfo* p_spriteInfo ) : GameObject(p_spriteInfo)
{
	if(p_spriteInfo != NULL)
		m_origin = p_spriteInfo->transformInfo;
}

Glyph::~Glyph()
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

bool Glyph::getVisibility()
{
	if(m_spriteInfo != NULL)
		return m_spriteInfo->visible;
	else
		return false;
}

int Glyph::setVisibility( bool p_set )
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

void Glyph::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_spriteInfo->transformInfo = m_origin;
}

void Glyph::animate( GlyphAnimation* p_animation, float p_freq, float p_amplitude, float p_speed )
{
	TransformInfo pos = m_origin;

	if( p_animation != NULL)
		pos = p_animation->getAnimation( m_origin, p_freq, p_amplitude, p_speed );

	m_spriteInfo->transformInfo = pos;
}
