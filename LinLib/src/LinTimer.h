#ifndef LINTIMER_H
#define LINTIMER_H

/*
#define BOOST_CHRONO_HEADER_ONLY
#define BOOST_ERROR_CODE_HEADER_ONLY
#include <boost/chrono.hpp>
*/

// #include "boost/date_time/posix_time/posix_time.hpp"

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
	Timer* newInstance();
};

#endif

/*#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    struct timeval start, end;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    usleep(2000);
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;
}*/
