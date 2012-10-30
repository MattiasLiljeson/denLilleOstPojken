#include "Animation.h"

Animation::Animation(fVector2 p_start, float p_frameWidth, float p_frameHeight, unsigned int p_frameCount, float p_delay, bool p_loop)
{
	m_currentFrame = 0;
	m_frameCount = p_frameCount;
	m_delay = p_delay;
	m_frameWidth = p_frameWidth;
	m_frameHeight = p_frameHeight;
	m_start = p_start;
	m_dt = 0;
	m_loop = p_loop;
}
void Animation::update(float p_dt)
{
	m_dt += p_dt;
	if (m_dt > m_delay)
	{
		m_dt -= m_delay;
		m_currentFrame++;
		if (m_loop && m_currentFrame >= m_frameCount)
			m_currentFrame = 0;
			
	}
}
Rect Animation::getCurrentFrame()
{
	Rect r;
	r.x = (int)( m_start.x + m_frameWidth*m_currentFrame );
	r.y = (int)( m_start.y );
	r.width = (int)( m_frameWidth );
	r.height = (int)( m_frameHeight );
	return r;
}
bool Animation::hasFinished()
{
	return m_currentFrame >= m_frameCount;
}
void Animation::restart()
{
	m_currentFrame = 0;
	m_dt = 0;
}