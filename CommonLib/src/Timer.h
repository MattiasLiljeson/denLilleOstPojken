#ifndef TIMER_H
#define TIMER_H

class Timer
{
protected:
	double	mDeltaTime;
	double  mElapsedTime;
	bool	mRunning;
public:
					Timer();
	virtual void	start() = 0;
	virtual void	stop()	= 0;
	virtual void	tick()	= 0;
	virtual Timer*	newInstance() = 0;
	double			getDeltaTime();
	double			getElapsedTime();
	bool			isStopped();
	bool			isPaused();
	virtual void	pause() = 0;
};

#endif