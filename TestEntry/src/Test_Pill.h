#ifndef TESTPILL_H
#define TESTPILL_H

#include "Test.h"
#include <Pill.h>
#include <Tilemap.h>

class Test_Pill: public Test
{
private:
public:
	Test_Pill(): Test("PILL")
	{
	}
	void setup()
	{
		Pill pill(NULL, NULL, NULL, NULL);
		newEntry(TestData("Position", pill.getPostion() == fVector2(0, 0)));
		newEntry(TestData("Not Consumed", !pill.isConsumed()));
		pill.consume();
		newEntry(TestData("Consumed", pill.isConsumed()));
	}	
};	

#endif