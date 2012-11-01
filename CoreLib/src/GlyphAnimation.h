
#ifndef GLYPHANIMATION_H
#define GLYPHANIMATION_H

#include "TransformInfo.h"
#include "fVector3.h"

class GlyphAnimation
{
public:
	GlyphAnimation(){};
	virtual void update( float p_dt ) = 0;
	virtual TransformInfo getAnimation( TransformInfo p_transInfo,
		float p_freq,  float p_amplitude, float p_speed ) = 0;
	virtual void reset() = 0;
};
#endif // GLYPHANIMATION_H