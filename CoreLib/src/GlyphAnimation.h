
#ifndef GLYPHANIMATION_H
#define GLYPHANIMATION_H

#include "fVector3.h"

class GlyphAnimation
{
public:
	GlyphAnimation(){};
	virtual void update( float p_dt ) = 0;
	virtual fVector3 getAnimation( fVector3 p_pos, float p_freq,
		float p_amplitude, float p_speed ) = 0;
};
#endif // GLYPHANIMATION_H