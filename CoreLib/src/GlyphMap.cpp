#include "GlyphMap.h"

GlyphMap::GlyphMap(const string& p_key, const string& p_bitmapPath, 
				   unsigned int p_charWidth, unsigned int p_charHeight)
{
	m_key = p_key;
	m_bitmapPath = p_bitmapPath;
	m_charWidth = p_charWidth;
	m_charHeight = p_charHeight;
	m_maxBitmapWidth = m_charWidth*p_key.length();
}

Rect GlyphMap::getCharRect(char p_character)
{
	// Get index position in bitmap
	int index = 0;
	for (unsigned int i=0;i<m_key.length();i++)
	{
		if (m_key[i]==p_character)
		{
			index = static_cast<int>(i);
			break;
		}
	}
	return Rect(index*m_charWidth, 0, m_charWidth, m_charHeight);
}