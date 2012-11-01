#include "GlyphAnimIn.h"

GlyphAnimIn::GlyphAnimIn()
{
	reset();
}

void GlyphAnimIn::update( float p_dt )
{
	m_totTime += p_dt;
}

TransformInfo GlyphAnimIn::getAnimation( TransformInfo p_transInfo,
	float p_freq, float p_amplitude, float p_speed )
{
	float fac = m_totTime / p_speed;
	float posX = p_transInfo.translation[TransformInfo::X];
	float scaleX = p_transInfo.scale[TransformInfo::X];

	posX *= fac;
	if(posX > p_transInfo.translation[TransformInfo::X])
		posX = p_transInfo.translation[TransformInfo::X];
	scaleX *= fac; 

	p_transInfo.translation[TransformInfo::X] = posX;
	p_transInfo.scale[TransformInfo::X] = scaleX;
	p_transInfo.translation[TransformInfo::X] = posX;
	return p_transInfo;
}

void GlyphAnimIn::reset()
{
	m_totTime = 0.0f;
}