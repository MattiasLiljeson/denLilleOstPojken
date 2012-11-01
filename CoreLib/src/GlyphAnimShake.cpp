#include "GlyphAnimShake.h"

GlyphAnimShake::GlyphAnimShake()
{
	reset();
}

void GlyphAnimShake::update( float p_dt )
{
	m_totTime += p_dt;
}

TransformInfo GlyphAnimShake::getAnimation( TransformInfo p_transInfo,
	float p_freq, float p_amplitude, float p_speed )
{
	float posX = p_transInfo.translation[TransformInfo::X];
	float scaX = p_transInfo.scale[TransformInfo::X];
	float scaY = p_transInfo.scale[TransformInfo::Y];

	float fac = abs(sin(posX*p_freq + m_totTime*p_speed))*p_amplitude;
	scaX += fac;
	scaY += fac;

	p_transInfo.scale[TransformInfo::X] = scaX;
	p_transInfo.scale[TransformInfo::Y] = scaY;

	return p_transInfo;
}

void GlyphAnimShake::reset()
{
	m_totTime = 0.0f;
}