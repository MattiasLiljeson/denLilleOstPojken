#ifndef LINTIMER_H
#define LINTIMER_H


#include <Timer.h>
#include <inttypes.h>
#include <time.h>
#include <iostream>
#include <errno.h>
using namespace std;

class LinTimer: public Timer
{
private:
	timespec m_freq;
	timespec m_currentTime;
	timespec diff(const timespec& start, const timespec& end);
	clockid_t m_timerType;
public:
	LinTimer();
	void start();
	void stop();
	void tick();
	void pause();
	Timer* newInstance();
};

#endif
