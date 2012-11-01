#ifndef GLYPHANIMSHAKE_H
#define GLYPHANIMSHAKE_H

#include <cmath>
#include "GlyphAnimation.h"

class GlyphAnimShake : public GlyphAnimation
{
private:
	float m_totTime;
public:
	GlyphAnimShake();
	void update( float p_dt );
	TransformInfo getAnimation( TransformInfo p_transInfo,
		float p_freq, float p_amplitude, float p_speed );
	virtual void reset();
};
#endif // GLYPHANIMSHAKE_H