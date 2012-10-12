#ifndef TESTFVECTOR3_H
#define TESTFVECTOR3_H

#include "Test.h"
#include <fVector3.h>

class Test_fVector3: public Test
{
private:
public:
	Test_fVector3(): Test("FVECTOR3")
	{
	}
	void setup()
	{
		fVector3 v1(1, 1, 1);
		fVector3 v2(1, 2, 3);
		newEntry(TestData("Construction", v1.x == 1 && v1.y == 1 && v1.z == 1));
		newEntry(TestData("Addition", v1 + v2 == fVector3(2, 3, 4)));
		newEntry(TestData("Subtraction", v1 - v2 == fVector3(0, -1, -2)));
		newEntry(TestData( "Scalar Mul", v1 * 2 == fVector3(2, 2, 2)));
		newEntry(TestData( "Scalar Div", v1 / 2 == fVector3(0.5f, 0.5f, 0.5f)));
		newEntry(TestData("Dot Product", v1.dot(v2) == 6));
		newEntry( TestData("Length", v1.length() == sqrt(3.0f)));
		newEntry(TestData("Length Squared", v1.lengthSquared() == 3));
		newEntry(TestData("Cross Product", v1.cross(v2) == fVector3(1, -2, 1)));
	}	
};	

#endif