#include "TextArea.h"


TextArea::TextArea(GlyphMap* p_glyphMap, unsigned int p_maxLength, GOFactory* p_factory, 
				   float p_xOrigin, float p_yOrigin)
{
	m_glyphMap = p_glyphMap;
	m_maxLength = p_maxLength;
	m_xOrigin = p_xOrigin;
	m_yOrigin = p_yOrigin;
	m_text = "";
	// Prepare glyph pool
	string texturePath = m_glyphMap->getPath();
	float glyphWidth = static_cast<float>(m_glyphMap->getCharWidth());
	float glyphHeight = static_cast<float>(m_glyphMap->getCharHeight());
	for (int i=0;i<m_maxLength;i++)
	{
		// TODO:
		// Right now text will always be left-bottom-aligned,
		// add anchors and/or alignment properties later:
		// LEFT-TOP,LEFT-BOTTOM,RIGHT-TOP,RIGHT-BOTTOM,CENTER    (at least)
		Glyph* g = p_factory->CreateGlyph(texturePath,
										  p_xOrigin+(float)i*glyphWidth,
										  p_yOrigin,fVector2(glyphWidth,glyphHeight));

		m_glyphs.push_back(g);
	}
}

TextArea::~TextArea()
{
	for (int i=0;i<m_maxLength;i++)
		delete m_glyphs[i];
	
	m_glyphs.clear();
}

void TextArea::setText(const string& p_text)
{
	if (p_text!=m_text)
	{
		m_text = p_text.substr(0,m_maxLength);
		for (unsigned int i=0;i<m_maxLength;i++)
		{
			Glyph* g = m_glyphs[i];
			if (i<m_text.length())
			{
				g->setRect(m_glyphMap->getCharRect(m_text[i]));
				g->setVisibility(true);
			}
			else
				g->setVisibility(false);
		}
	}
}

void TextArea::update(float p_deltaTime, InputInfo p_inputInfo)
{
	for (unsigned int i=0;i<m_glyphs.size();i++)
	{
		m_glyphs[i]->update(p_deltaTime,p_inputInfo);
	}
}