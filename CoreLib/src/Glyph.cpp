#include "Glyph.h"

Glyph::Glyph( SpriteInfo* p_spriteInfo, GlyphAnimation* p_anim8or ) : GameObject(p_spriteInfo)
{
	m_anim8or = p_anim8or;
	m_origin = p_spriteInfo->transformInfo;
}

Glyph::~Glyph()
{
	delete m_anim8or;
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
	if( m_anim8or != NULL )
	{
		m_anim8or->update( p_deltaTime );
	}
	m_spriteInfo->transformInfo = m_origin;
}

void Glyph::animate( float p_freq, float p_amplitude, float p_speed )
{
	TransformInfo pos = m_origin;

	if( m_anim8or != NULL )
	{
		pos = m_anim8or->getAnimation( m_origin, p_freq, p_amplitude, p_speed );
	}

	m_spriteInfo->transformInfo = pos;
}
