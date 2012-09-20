#include "WinTimer.h"

WinTimer::WinTimer(): Timer()
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;

	mCurrentTime = 0;
}
void WinTimer::start()
{
	if (!mRunning)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&mCurrentTime);
		mRunning = true;
	}
}
void WinTimer::stop()
{
	mRunning = false;
}
void WinTimer::tick()
{
	if (mRunning)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mDeltaTime = (currTime - mCurrentTime)*mSecondsPerCount;
		mElapsedTime += mDeltaTime;
		mCurrentTime = currTime;
	}
}