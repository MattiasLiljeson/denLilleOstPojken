#ifndef TESTSUPERPILL_H
#define TESTSUPERPILL_H

#include "Test.h"
#include <SuperPill.h>
#include <Tilemap.h>
#include <GameStats.h>

class Test_SuperPill: public Test
{
private:
public:
	Test_SuperPill(): Test("SUPERPILL")
	{
	}
	void setup()
	{
		GameStats stats(NULL);
		SuperPill pill(NULL, NULL, &stats,NULL);
		newEntry(TestData("Position", pill.getPostion() == fVector2(0, 0)));
		newEntry(TestData("Not Consumed", !pill.isConsumed()));
		newEntry(TestData("Not Super", !stats.isSuperMode()));
		pill.consume();
		newEntry(TestData("Consumed", pill.isConsumed()));
		newEntry(TestData("Super", stats.isSuperMode()));
	}	
};	

#endif