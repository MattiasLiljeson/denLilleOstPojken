#ifndef LINTIMER_H
#define LINTIMER_H

#include "Timer.h"

class LinTimer: public Timer
{
private:

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