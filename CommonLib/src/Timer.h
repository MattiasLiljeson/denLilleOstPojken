#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	virtual ~Timer();
	
	void start();
	void stop();
	void tick();
	double getDeltaTime();
private:

};

#endif