#include "TextArea.h"

fVector2 TextArea::getGlyphRelPos( int p_idx, ANCHOR p_anchor )
{
	fVector2 pos;
	pos.x = calcAnchorOffsetX( p_idx, p_anchor);
	pos.y = calcAnchorOffsetY( p_idx, p_anchor);
	return pos;
}

fVector2 TextArea::getGlyphAbsPos( int p_idx, ANCHOR p_anchor )
{
	fVector2 pos;
	pos.x = getGlyphAbsPosX( p_idx, p_anchor );
	pos.y = getGlyphAbsPosY( p_idx, p_anchor );
	return pos;
}

int TextArea::setGlyphPos( int p_idx, ANCHOR p_anchor, fVector2 p_textOrigin )
{
	float x = calcAnchorOffsetX( p_idx, p_anchor ) + m_xOrigin;
	float y = calcAnchorOffsetY( p_idx, p_anchor ) + m_yOrigin;

	SpriteInfo* sprInfo = m_glyphs[p_idx]->getSpriteInfo();
	if(sprInfo != NULL)
	{
		sprInfo->transformInfo.translation[TransformInfo::X] = x;
		sprInfo->transformInfo.translation[TransformInfo::Y] = y;
		return GAME_OK;
	}
	else
	{
		return GAME_FAIL;
	}
}

float TextArea::getGlyphAbsPosX( int p_idx, ANCHOR p_anchor )
{
	return m_xOrigin + calcAnchorOffsetX( p_idx, p_anchor);
}

float TextArea::getGlyphAbsPosY( int p_idx, ANCHOR p_anchor )
{
	return m_yOrigin + calcAnchorOffsetY( p_idx, p_anchor);
}

float TextArea::calcAnchorOffsetX( int p_idx, ANCHOR p_anchor )
{
	float charWidth = m_glyphMap->getCharWidth() * m_glyphScale.x;
	float textLength = m_maxLength*charWidth;

	if(p_anchor == TOP_LEFT || p_anchor == CEN_LEFT || p_anchor == BOT_LEFT)
		return  charWidth*0.5f + p_idx*charWidth;

	if(p_anchor == TOP_CENTER || p_anchor == CEN_CENTER || p_anchor == BOT_CENTER)
		return textLength*-0.5f + p_idx*charWidth;

	if(p_anchor == TOP_RIGHT || p_anchor == CEN_RIGHT || p_anchor == BOT_RIGHT)
		return charWidth*0.5f -textLength + p_idx*charWidth;

	return (float)GAME_FAIL;
}

float TextArea::calcAnchorOffsetY( int p_idx, ANCHOR p_anchor )
{
	float textHeight = m_glyphMap->getCharHeight() * m_glyphScale.y;

	if(p_anchor == TOP_LEFT || p_anchor == TOP_CENTER || p_anchor == TOP_RIGHT)
		return  textHeight*0.5f;

	if(p_anchor == CEN_LEFT || p_anchor == CEN_CENTER || p_anchor == CEN_RIGHT)
		return 0.0f; //m_glyphMap->getCharHeight();

	if(p_anchor == BOT_LEFT || p_anchor == BOT_CENTER || p_anchor == BOT_RIGHT)
		return textHeight*-0.5f;

	return (float)GAME_FAIL;
}

TextArea::TextArea( GlyphMap* p_glyphMap, unsigned int p_maxLength,
	GOFactory* p_factory, float p_xOrigin, float p_yOrigin,
	ANCHOR p_anchor, fVector2 p_glyphScale, vector<GlyphAnimation*> p_animators )
{
	m_glyphMap = p_glyphMap;
	m_maxLength = p_maxLength;
	m_xOrigin = p_xOrigin;
	m_yOrigin = p_yOrigin;
	m_currAnchor = p_anchor;
	m_text = "";
	m_glyphScale = p_glyphScale;

	// Prepare glyph pool
	string texturePath = m_glyphMap->getPath();
	float glyphWidth = (float)(m_glyphMap->getCharWidth()) * p_glyphScale.x;
	float glyphHeight = (float)(m_glyphMap->getCharHeight()) * p_glyphScale.y;

	m_animators = p_animators;

	for (unsigned int i=0;i<m_maxLength;i++)
	{
		Glyph* g = p_factory->CreateGlyph( texturePath,
			getGlyphAbsPosX(i, p_anchor), getGlyphAbsPosY(i, p_anchor), 
			fVector2(glyphWidth, glyphHeight));

		m_glyphs.push_back(g);
	}

}

TextArea::~TextArea()
{
	for (unsigned int i=0;i<m_maxLength;i++)
	{
		delete m_glyphs[i];
		m_glyphs[i] = NULL;
	}
	m_glyphs.clear();
	if(m_glyphMap != NULL)
		delete m_glyphMap;
	m_glyphMap = NULL;

	for( unsigned int i=0; i<m_animators.size(); i++ )
	{
		delete m_animators[i];
		m_animators[i] = NULL;
	}
}

int TextArea::setText(const string& p_text)
{
	int tooLong = GAME_OK;
	if (p_text != m_text)
	{
		if(p_text.length() > m_maxLength)
			tooLong = GAME_FAIL;

		m_text = p_text.substr(0, m_maxLength);
		for (unsigned int i=0; i<m_maxLength; i++)
		{
			Glyph* g = m_glyphs[i];
			if (i<m_text.length())
			{
				g->setRect( m_glyphMap->getCharRect(m_text[i]) );
				g->setVisibility( true );
			}
			else
				g->setVisibility( false );
		}
	}

	return tooLong;
}

void TextArea::update(float p_deltaTime, InputInfo p_inputInfo)
{
	for( unsigned int i=0; i<m_glyphs.size(); i++ )
	{
		m_glyphs[i]->update( p_deltaTime, p_inputInfo );
	}
	for( unsigned int i=0; i<m_animators.size(); i++ )
	{
		m_animators[i]->update( p_deltaTime );
	}
}

void TextArea::animateText( float p_freq, float p_amplitude, float p_speed, int p_animIdx )
{
	for( unsigned int i=0; i<m_glyphs.size(); i++ )
	{
		if( (unsigned int) p_animIdx < m_animators.size() )
			m_glyphs[i]->animate(m_animators[p_animIdx], p_freq, p_amplitude, p_speed);
	}
}

void TextArea::resetAnimation( int p_idx )
{
	if( (unsigned int) p_idx < m_animators.size() )
		m_animators[p_idx]->reset();
}

void TextArea::setOrigin( fVector2 p_newOrigin )
{
	m_xOrigin = p_newOrigin.x;
	m_yOrigin = p_newOrigin.y;
	for( unsigned int i=0; i<m_glyphs.size(); i++ )
	{
		setGlyphPos( i, m_currAnchor, p_newOrigin );
	}
}

bool TextArea::getVisible()
{
	// HACK: returns only the first elments visibility
	return m_glyphs[0]->getVisibility();
}

void TextArea::setVisible( bool p_visible )
{
	for( unsigned int i=0; i<m_glyphs.size(); i++ )
	{
		m_glyphs[i]->setVisibility( p_visible );
	}
}