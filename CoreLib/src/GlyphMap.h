#ifndef GLYPHMAP_H
#define GLYPHMAP_H

#include <string>
using namespace std;

// GlyphMap contains a path for a bitmap font a
// key string that defines the characters present 
// in the bitmap
class GlyphMap
{
public:
	GlyphMap(const string& key, const string& bitmapPath, 
			unsigned int charWidth, unsigned int charHeight);
	virtual ~GlyphMap() {}
	const int GetWidth() const {return m_charWidth;}
	const int GetHeight() const {return m_charHeight;}
	const string& GetPath() const {return m_bitmapPath;}

private:
	string m_key;
	string m_bitmapPath;
	unsigned int m_charWidth;
	unsigned int m_charHeight;
};

#endif