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
		m_entries.push_back(TestData("Construction", v1.x == 1 && v1.y == 1));
		m_entries.push_back(TestData("Addition", v1 + v2 == fVector2(2, 3)));
		m_entries.push_back(TestData("Subtraction", v1 - v2 == fVector2(0, -1)));
		m_entries.push_back(TestData( "Scalar Mul", v1 * 2 == fVector2(2, 2)));
		m_entries.push_back(TestData( "Scalar Div", v1 / 2 == fVector2(0.5f, 0.5f)));
		m_entries.push_back(TestData("Dot Product", v1.dot(v2) == 3));
		m_entries.push_back( TestData("Length", v3.length() == 5));
		m_entries.push_back(TestData("Length Squared", v3.lengthSquared() == 25));
		m_entries.push_back(TestData("Cross Product", v3.cross(v2) == 2));
	}	
};		
							   		
#endif	