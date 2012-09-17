#ifndef WINTIMER_H
#define WINTIMER_H

#include <windows.h>
#include "Timer.h"

class WinTimer: public Timer
{
private:
	double	mSecondsPerCount;
	__int64 mCurrentTime;

public:
	WinTimer();
	void start();
	void stop();
	void tick();
};

#endif