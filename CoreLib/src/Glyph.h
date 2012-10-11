#ifndef GLYPH_H
#define GLYPH_H

#include "GameObject.h"


// A glyph(character) for a textarea
class Glyph : public GameObject
{
public:
	Glyph(SpriteInfo* p_spriteInfo);
	virtual			~Glyph();
	void			setRect(Rect p_rect);
	void			setVisibility(bool p_visible);
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
protected:

};


#endif
