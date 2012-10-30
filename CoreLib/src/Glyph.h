#ifndef GLYPH_H
#define GLYPH_H

//#include <vector>
#include "GlyphAnimSinus.h"
#include "GameObject.h"
#include "CommonUtility.h"

using namespace std;

class Glyph : public GameObject
{
private:
	TransformInfo m_origin;

public:
	Glyph( SpriteInfo* p_spriteInfo );
	virtual			~Glyph();
	int				setRect(Rect p_rect);
	int				setVisibility(bool p_visible);
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
	void			animate( GlyphAnimation* p_animation, float p_freq, float p_amplitude, float p_speed );
};


#endif
