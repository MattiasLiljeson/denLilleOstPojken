#include "LinTimer.h"

LinTimer::LinTimer(): Timer()
{
}
void LinTimer::start()
{
}
void LinTimer::stop()
{
}
void LinTimer::tick()
{
}
Timer* LinTimer::newInstance()
{
	LinTimer* newLinTimer = new LinTimer();
	return newLinTimer;
}