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
	// This enum is defined here, at the top. The definition must be on top 
	// of variables using it as a data type. Otherwise the compiler won't
	// find it
public:
	enum ANCHOR {
		TOP_LEFT, TOP_CENTER, TOP_RIGHT,
		CEN_LEFT, CEN_CENTER, CEN_RIGHT,
		BOT_LEFT, BOT_CENTER, BOT_RIGHT
	};

	// Vars declared below
private:
	vector<Glyph*> m_glyphs;
	GlyphMap* m_glyphMap;
	unsigned int m_maxLength;
	string m_text;
	ANCHOR m_currAnchor;
	float m_xOrigin;
	float m_yOrigin;
	fVector2 m_glyphScale;

private: 
	fVector2 getGlyphRelPos( int p_idx, ANCHOR p_anchor );
	fVector2 getGlyphAbsPos( int p_idx, ANCHOR p_anchor );

	int setGlyphPos( int p_idx, ANCHOR p_anchor, fVector2 p_textOrigin );

	float getGlyphAbsPosX( int p_idx, ANCHOR p_anchor );
	float getGlyphAbsPosY( int p_idx, ANCHOR p_anchor );

	float calcAnchorOffsetX( int p_idx, ANCHOR p_anchor );
	float calcAnchorOffsetY( int p_idx, ANCHOR p_anchor );

public:
	TextArea( GlyphMap* p_glyphMap, unsigned int p_maxLength, GOFactory* p_factory, 
			 float p_xOrigin, float p_yOrigin, ANCHOR p_anchor, fVector2 p_glyphScale );
	virtual			~TextArea();

	const string&	getText() const {return m_text;}

	/** Sets the text presented by this TextArea
	* @return GAME_FAIL if the submitted string is longer than maxlength of
	* this textArea.
	*/
	int				setText(const string& p_text);

	unsigned int	getMaxLength() const {return m_maxLength;}
	void			update(float p_deltaTime, InputInfo p_inputInfo);

	float			getOriginX(){return m_xOrigin;}
	float			getOriginY(){return m_yOrigin;}
	void			setOrigin( fVector2 p_newOrigin );
};

#endif