#include "GlyphAnimOut.h"

GlyphAnimOut::GlyphAnimOut()
{
	reset();
}

void GlyphAnimOut::update( float p_dt )
{
	m_totTime += p_dt;
}

TransformInfo GlyphAnimOut::getAnimation( TransformInfo p_transInfo,
	float p_freq, float p_amplitude, float p_speed )
{
	float fac = m_totTime / p_speed;
	float posX = p_transInfo.translation[TransformInfo::X];
	float scaleX = p_transInfo.scale[TransformInfo::X];
	
	posX = posX - posX * fac;
	scaleX *= 1.0f - fac; 

	p_transInfo.translation[TransformInfo::X] = posX;
	p_transInfo.scale[TransformInfo::X] = scaleX;

	return p_transInfo;
}

void GlyphAnimOut::reset()
{
	m_totTime = 0.0f;
}