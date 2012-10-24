#ifndef GLYPHANIMSINUS_H
#define GLYPHANIMSINUS_H

#include <cmath>
#include "GlyphAnimation.h"

class GlyphAnimSinus : public GlyphAnimation
{
private:
	float m_totTime;
public:
	GlyphAnimSinus();
	void update( float p_dt );
	fVector3 getAnimation( fVector3 p_pos, float p_freq,
		float p_amplitude, float p_speed );
};
#endif // GLYPHANIMSINUS_H