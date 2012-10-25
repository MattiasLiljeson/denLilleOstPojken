#ifndef GLYPH_H
#define GLYPH_H

#include "GlyphAnimSinus.h"
#include "GameObject.h"
#include "CommonUtility.h"

// A glyph(character) for a textarea
class Glyph : public GameObject
{
private:
	TransformInfo m_origin;
	GlyphAnimation* m_anim8or;

public:
	Glyph(SpriteInfo* p_spriteInfo, GlyphAnimation* p_anim8or = NULL);
	virtual			~Glyph();
	int				setRect(Rect p_rect);
	int				setVisibility(bool p_visible);
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
	void			animate( float p_freq, float p_amplitude, float p_speed );
};


#endif
