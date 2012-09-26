#ifndef T_TIMER_H
#define T_TIMER_H

#include <WinTimer.h>
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
		winTimer->start();
	}
	virtual void TearDown(){
		winTimer->stop();
		delete winTimer;
	}
	WinTimer* winTimer;
};

TEST_F(T_Timer, CheckIfTheTimerIsDone){
	ASSERT_EQ(winTimer->getDeltaTime(), winTimer->getElapsedTime());
}
#endif