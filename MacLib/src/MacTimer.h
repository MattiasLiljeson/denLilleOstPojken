#ifndef LINTIMER_H
#define LINTIMER_H

#include <Timer.h>
// Why not just use SFML's timer? Makes life easy for me. :)
#include <SFML/System.hpp>

class LinTimer: public Timer
{
private:
    sf::Clock clock;
    double m_currentTime;
public:
	LinTimer();
	void start();
	void stop();
	void tick();
	void pause();
	Timer* newInstance();
};

#endif
