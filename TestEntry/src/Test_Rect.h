#ifndef TESTRECT_H
#define TESTRECT_H

#include "Test.h"
#include <Rect.h>

class Test_Rect: public Test
{
private:
public:
	Test_Rect(): Test("CIRCLE")
	{
	}
	void setup()
	{
		Rect r(0, 0, 10, 10);
		newEntry(TestData("Construction", r.x == 0 &&
													 r.y == 0 &&
													 r.width == 10 &&
													 r.height == 10));
	}	
};	

#endif