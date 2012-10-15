#ifndef TESTCIRCLE_H
#define TESTCIRCLE_H

#include "Test.h"
#include <Circle.h>

class Test_Circle: public Test
{
private:
public:
	Test_Circle(): Test("CIRCLE")
	{
	}
	void setup()
	{
		Circle c1(fVector2(0, 0), 10);
		Circle c2(fVector2(10, 0), 10);
		Circle c3(fVector2(30, 0), 10);
		newEntry(TestData("Position", c1.c == fVector2(0, 0)));
		newEntry(TestData("Radius", c1.r == 10));
		newEntry(TestData("Collision", c1.collidesWith(c2)));
		newEntry(TestData("No Collision", !c1.collidesWith(c3)));
	}	
};	

#endif