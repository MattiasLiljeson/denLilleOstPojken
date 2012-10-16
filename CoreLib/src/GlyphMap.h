#ifndef GLYPHMAP_H
#define GLYPHMAP_H

#include <string>
#include "Rect.h"
using namespace std;

// GlyphMap contains a path for a bitmap font a
// key string that defines the characters present 
// in the bitmap
class GlyphMap
{
private:
	string m_key;
	string m_bitmapPath;
	unsigned int m_charWidth;
	unsigned int m_charHeight;
	unsigned int m_maxBitmapWidth;

public:
	GlyphMap(const string& p_key, const string& p_bitmapPath, 
			unsigned int p_charWidth, unsigned int p_charHeight);
	virtual ~GlyphMap() {}
	unsigned int getCharWidth() const {return m_charWidth;}
	unsigned int getCharHeight() const {return m_charHeight;}
	unsigned int getMaxBitmapWidth() const {return m_maxBitmapWidth;} 
	const string& getPath() const {return m_bitmapPath;}
	Rect getCharRect(char p_character);
};

#endif