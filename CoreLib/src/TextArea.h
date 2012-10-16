#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <vector>
#include "Glyph.h"
#include "GlyphMap.h"
#include "GOFactory.h"
using namespace std;

// Textarea contains a bunch of characters and their origin position and anchor

// Pre defs
class Glyph;
class GlyphMap;
class GOFactory;

class TextArea
{
private:
	vector<Glyph*> m_glyphs;
	GlyphMap* m_glyphMap;
	unsigned int m_maxLength;
	string m_text;
	float m_xOrigin, m_yOrigin;

private:
	int glyphPosX( int p_idx);
	int glyphPosY( int p_idx);

public:
	TextArea(GlyphMap* p_glyphMap, unsigned int p_maxLength, GOFactory* p_factory, 
			 float p_xOrigin, float p_yOrigin); // TODO: Add anchor enum
	virtual			~TextArea();

	const string&	getText() const {return m_text;}
	void			setText(const string& p_text);

	unsigned int	getMaxLength() const {return m_maxLength;}
	void			update(float p_deltaTime, InputInfo p_inputInfo);

	int				getOriginX(){return m_xOrigin;}
	int				getOriginY(){return m_yOrigin;}
	void			setOrigin(float p_x, float p_y);
};

#endif