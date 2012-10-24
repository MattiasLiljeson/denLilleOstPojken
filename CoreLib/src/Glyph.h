#ifndef GLYPH_H
#define GLYPH_H

#include "GameObject.h"
#include "CommonUtility.h"

// A glyph(character) for a textarea
class Glyph : public GameObject
{
public:
	Glyph(SpriteInfo* p_spriteInfo);
	virtual			~Glyph();
	int				setRect(Rect p_rect);
	int				setVisibility(bool p_visible);
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
protected:

};


#endif
