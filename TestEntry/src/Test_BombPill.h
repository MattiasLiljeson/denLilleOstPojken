#ifndef BOMBSPEEDPILL_H
#define BOMBSPEEDPILL_H

#include "Test.h"
#include <BombPill.h>
#include <GameStats.h>

class Test_BombPill: public Test
{
private:
public:
	Test_BombPill(): Test("BOMBPILL")
	{
	}
	void setup()
	{
		GameStats stats(NULL);
		BombPill pill(NULL, NULL, &stats, NULL);
		newEntry(TestData("Position", pill.getPostion() == fVector2(0, 0)));
		newEntry(TestData("Not Consumed", !pill.isConsumed()));
		newEntry(TestData("No bomb", stats.getItemSlot() != 0));
		pill.consume();
		newEntry(TestData("Consumed", pill.isConsumed()));
		newEntry(TestData("Registered", stats.getItemSlot() == 0));
		
	}	
};	

#endif