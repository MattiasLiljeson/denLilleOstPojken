#ifndef T_TIMER_H
#define T_TIMER_H

#include <WinTimer.h>
#include <LinTimer.h>
#include "gtest/gtest.h"

class T_Timer : public ::testing::Test
{
protected:
	T_Timer(){
	}
	virtual ~T_Timer(){
	}
	virtual void SetUp(){
		winTimer = new WinTimer();
		linTimer = new LinTimer();
	}
	virtual void TearDown(){
		delete winTimer;
		delete linTimer;
	}
	WinTimer* winTimer;
	LinTimer* linTimer;
};

TEST_F(T_Timer, CheckWinTimerIfTheTimerIsDone){
	winTimer->start();
	ASSERT_EQ(winTimer->getDeltaTime(), winTimer->getElapsedTime());
}

TEST_F(T_Timer, ChekcLinTimerIfTheTimerIsDone){
	linTimer->start();
	ASSERT_EQ(linTimer->getDeltaTime(), linTimer->getElapsedTime());
}

#endif