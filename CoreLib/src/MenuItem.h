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
	bool m_selectable;
	fVector2 m_basePosition;
	fVector2 m_textOffset; 
	TextArea* m_text;

private:
	int updateText();
	int updateSprite();

public:
	MenuItem( SpriteInfo* p_spriteInfo, TextArea* p_text,
		fVector2 p_basePosition, fVector2 p_textOffset);
	virtual ~MenuItem();

	void update(float p_deltaTime, InputInfo p_inputInfo);
	void animateText( float p_freq, float p_amplitude, float p_speed, int p_animIdx );
	void resetAnimation( int p_idx );
	TextArea* getTextArea();

	int setTextOffset( float p_x, float p_y );
	int setBasePosition( float p_x, float p_y );

	void setVisible(bool p_visible);
	void setSelectable( bool p_selectable );
	bool isSelectable();

};

#endif