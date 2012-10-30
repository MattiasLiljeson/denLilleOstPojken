#include "GlyphAnimSinus.h"

GlyphAnimSinus::GlyphAnimSinus()
{
	reset();
}

void GlyphAnimSinus::update( float p_dt )
{
	m_totTime += p_dt;
}

TransformInfo GlyphAnimSinus::getAnimation( TransformInfo p_transInfo,
	float p_freq, float p_amplitude, float p_speed )
{
	float posX = p_transInfo.translation[TransformInfo::X];
	float posY = p_transInfo.translation[TransformInfo::Y];
	float scaX = p_transInfo.scale[TransformInfo::X];
	float scaY = p_transInfo.scale[TransformInfo::Y];
	float fac = sin(posX*p_freq + m_totTime*p_speed)*p_amplitude;
	posY += fac;
	scaX -= fac/p_amplitude;
	scaY += fac/p_amplitude;


	p_transInfo.translation[TransformInfo::X] = posX;
	p_transInfo.translation[TransformInfo::Y] = posY;
	p_transInfo.scale[TransformInfo::X] = scaX;
	p_transInfo.scale[TransformInfo::Y] = scaY;

	// Rotation does not work
	//p_transInfo.rotation[TransformInfo::X] = scaY;
	//p_transInfo.rotation[TransformInfo::Y] = scaY;
	//p_transInfo.rotation[TransformInfo::Z] = scaY;

	return p_transInfo;
}

void GlyphAnimSinus::reset()
{
	m_totTime = 0.0f;
}