#include "Timer.h"

Timer::Timer()
{
	mDeltaTime = mElapsedTime = 0.0;
	mRunning = false;
}
double Timer::getDeltaTime()
{
	if (mRunning)
		return mDeltaTime;
	return 0.0;
}
double Timer::getElapsedTime()
{
	return mElapsedTime;
}
bool Timer::isStopped()
{
	return !mRunning && mElapsedTime == 0.0;
}
bool Timer::isPaused()
{
	return !mRunning && !isStopped();
}