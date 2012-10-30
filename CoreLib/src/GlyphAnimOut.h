#ifndef GLYPHANIMOUT_H
#define GLYPHANIMOUT_H

#include <cmath>
#include "GlyphAnimation.h"

class GlyphAnimOut : public GlyphAnimation
{
private:
	float m_totTime;
public:
	GlyphAnimOut();
	void update( float p_dt );
	TransformInfo getAnimation( TransformInfo p_transInfo,
		float p_freq, float p_amplitude, float p_speed );
	virtual void reset();
};
#endif // GLYPHANIMOUT_H