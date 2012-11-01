#ifndef _WIN32
#include "LinTimer.h"

LinTimer::LinTimer(): Timer()
{
	/*
	   CLOCK_REALTIME
		  System-wide  realtime clock.  Setting this clock requires appro-
		  priate privileges.

       CLOCK_MONOTONIC
          Clock that cannot be set and  represents  monotonic  time  since
          some unspecified starting point.

       CLOCK_PROCESS_CPUTIME_ID
          High-resolution per-process timer from the CPU.

       CLOCK_THREAD_CPUTIME_ID
          Thread-specific CPU-time clock.
	*/
	m_timerType = CLOCK_MONOTONIC;
	if (clock_getres(m_timerType, &m_freq)==-1)
		cout<<"Clock get resolution error: "<<errno<<endl;
	else
	{
		cout<<"Clock resolution: sec: "<<m_freq.tv_sec<<" nsec: "<<m_freq.tv_nsec<<endl;
	}
}
void LinTimer::start()
{
	if (!mRunning)
	{
		if (clock_gettime(m_timerType, &m_currentTime)==-1)
        	cout<<"clock_gettime() failed on start";
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
		timespec now;
		if (clock_gettime(m_timerType, &now)==-1)
        		cout<<"clock_gettime() failed";
		mDeltaTime = (double)(diff(m_currentTime,now).tv_nsec) / (double)m_freq.tv_nsec/1000000000.0;
		mElapsedTime += mDeltaTime;
		cout<<"dt: "<<mDeltaTime<<endl;
		m_currentTime = now;
	}
}
Timer* LinTimer::newInstance()
{
	LinTimer* newLinTimer = new LinTimer();
	return newLinTimer;
}
timespec LinTimer::diff(const timespec& start, const timespec& end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) 
	{
		temp.tv_sec = end.tv_sec-start.tv_sec-1.0;
		temp.tv_nsec = 1000000000.0+end.tv_nsec-start.tv_nsec;
	} 
	else 
	{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
#endif