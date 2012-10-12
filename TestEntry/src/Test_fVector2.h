#ifndef TEST_FVECTOR2
#define TEST_FVECTOR2

#include "Test.h"
#include <fVector2.h>

class Test_fVector2: public Test
{
private:
public:
	Test_fVector2(): Test("FVECTOR2")
	{
	}
	void setup()
	{
		fVector2 v1(1, 1);
		fVector2 v2(1, 2);
		fVector2 v3(3, 4);
		newEntry(TestData("Construction", v1.x == 1 && v1.y == 1));
		newEntry(TestData("Addition", v1 + v2 == fVector2(2, 3)));
		newEntry(TestData("Subtraction", v1 - v2 == fVector2(0, -1)));
		newEntry(TestData( "Scalar Mul", v1 * 2 == fVector2(2, 2)));
		newEntry(TestData( "Scalar Div", v1 / 2 == fVector2(0.5f, 0.5f)));
		newEntry(TestData("Dot Product", v1.dot(v2) == 3));
		newEntry( TestData("Length", v3.length() == 5));
		newEntry(TestData("Length Squared", v3.lengthSquared() == 25));
		newEntry(TestData("Cross Product", v3.cross(v2) == 2));
	}	
};		
							   		
#endif	