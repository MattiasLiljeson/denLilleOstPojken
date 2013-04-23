#ifndef _WIN32
#include "MacTimer.h"

LinTimer::LinTimer(): Timer()
{
}

void LinTimer::start()
{
	if (!mRunning)
	{
		m_currentTime = clock.GetElapsedTime();
		mRunning = true;
	}
}
void LinTimer::stop()
{
	mRunning = false;
	mElapsedTime = 0;
}
void LinTimer::pause()
{
	mRunning = false;
}
void LinTimer::tick()
{
	if (mRunning)
	{
		mDeltaTime = clock.GetElapsedTime() - m_currentTime;
		mElapsedTime += mDeltaTime;
		m_currentTime = clock.GetElapsedTime();
	}
}
Timer* LinTimer::newInstance()
{
	LinTimer* newLinTimer = new LinTimer();
	return newLinTimer;
}

#endif