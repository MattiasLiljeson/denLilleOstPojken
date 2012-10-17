#ifndef TESTSPEEDPILL_H
#define TESTSPEEDPILL_H

#include "Test.h"
#include <SpeedPill.h>
#include <GameStats.h>

class Test_SpeedPill: public Test
{
private:
public:
	Test_SpeedPill(): Test("SPEEDPILL")
	{
	}
	void setup()
	{
		GameStats stats(NULL);
		SpeedPill pill(NULL, NULL, &stats, NULL);
		newEntry(TestData("Position", pill.getPostion() == fVector2(0, 0)));
		newEntry(TestData("Not Consumed", !pill.isConsumed()));
		newEntry(TestData("Not Speeded", stats.getBuffSlot() != 0));
		pill.consume();
		newEntry(TestData("Consumed", pill.isConsumed()));
		newEntry(TestData("Registered", stats.getBuffSlot() == 0));
	}	
};	

#endif