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
	mElapsedTime = 0;
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
}
void LinTimer::pause()
{
}
void LinTimer::tick()
{
	if (mRunning)
	{
		timespec now;
		if (clock_gettime(m_timerType, &now)==-1)
        	cout<<"clock_gettime() failed";
		mDeltaTime = (double)(diff(m_currentTime,now).tv_nsec/m_freq.tv_nsec*1000000000.0);
		mDeltaTime = 0.01;
		mElapsedTime += mDeltaTime;
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
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} 
	else 
	{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
/*
int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
*/
