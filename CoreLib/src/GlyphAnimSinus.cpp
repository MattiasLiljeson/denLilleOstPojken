#include "GlyphAnimSinus.h"

GlyphAnimSinus::GlyphAnimSinus()
{
	m_totTime = 0.0f;
}

void GlyphAnimSinus::update( float p_dt )
{
	m_totTime += p_dt;
}

fVector3 GlyphAnimSinus::getAnimation( fVector3 p_pos, float p_freq,
	float p_amplitude, float p_speed )
{
	float fac = sin(p_pos.x*p_speed + m_totTime*p_freq)*p_amplitude;
	p_pos.y += fac;
	return p_pos;
}



