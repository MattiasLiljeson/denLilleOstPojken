#ifndef GLYPHANIMIN_H
#define GLYPHANIMIN_H

#include <cmath>
#include "GlyphAnimation.h"

class GlyphAnimIn : public GlyphAnimation
{
private:
	float m_totTime;
public:
	GlyphAnimIn();
	void update( float p_dt );
	TransformInfo getAnimation( TransformInfo p_transInfo,
		float p_freq, float p_amplitude, float p_speed );
	virtual void reset();
};
#endif // GLYPHANIMIN_H