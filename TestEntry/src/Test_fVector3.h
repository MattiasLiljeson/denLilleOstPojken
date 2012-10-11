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
		m_entries.push_back(TestData("Construction", v1.x == 1 && v1.y == 1 && v1.z == 1));
		m_entries.push_back(TestData("Addition", v1 + v2 == fVector3(2, 3, 4)));
		m_entries.push_back(TestData("Subtraction", v1 - v2 == fVector3(0, -1, -2)));
		m_entries.push_back(TestData( "Scalar Mul", v1 * 2 == fVector3(2, 2, 2)));
		m_entries.push_back(TestData( "Scalar Div", v1 / 2 == fVector3(0.5f, 0.5f, 0.5f)));
		m_entries.push_back(TestData("Dot Product", v1.dot(v2) == 6));
		m_entries.push_back( TestData("Length", v1.length() == sqrt(3.0f)));
		m_entries.push_back(TestData("Length Squared", v1.lengthSquared() == 3));
		m_entries.push_back(TestData("Cross Product", v1.cross(v2) == fVector3(1, -2, 1)));
	}	
};	

#endif