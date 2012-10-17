#ifndef ANIMATION_H
#define ANIMATION_H

#include <fVector2.h>
#include <Rect.h>

//Class Controlling animation on a spritesheet
//It uses horizontal stepping to move between frames

class Animation
{
private:
	unsigned int m_currentFrame;
	unsigned int m_frameCount;
	float m_delay;
	float m_frameWidth;
	float m_frameHeight;
	fVector2 m_start;
	float m_dt;
public:
	Animation(fVector2 p_start, float p_frameWidth, float p_frameHeight, unsigned int p_frameCount, float p_delay);
	void update(float p_dt);
	Rect getCurrentFrame();
	bool hasFinished();
};

#endif