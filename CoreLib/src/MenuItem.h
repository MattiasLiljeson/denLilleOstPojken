#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
using namespace std;

// HACK: Change to factory..
#include "GameObject.h"
#include "GlyphMap.h"
#include "TextArea.h"

//predefs
class GameObject;
class GlyphMap;
class TextArea;

class MenuItem: public GameObject
{
private:
	fVector2 m_basePosition;
	fVector2 m_offset; 
	GlyphMap* m_font;
	TextArea* m_text;

private:
	void updateText();
	void updateSprite();

public:
	MenuItem(SpriteInfo* p_spriteInfo, TextArea* p_text, GlyphMap* p_font, fVector2 p_basePosition);
	virtual ~MenuItem();

	void update(float p_deltaTime, InputInfo p_inputInfo);

	TextArea* getTextArea();

	void setOffset( float p_x, float p_y );
	void setBasePosition( float p_x, float p_y );

};

#endif