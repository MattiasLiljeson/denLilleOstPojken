#ifndef TESTINPUTINFO_H
#define TESTINPUTINFO_H

#include "Test.h"
#include <InputInfo.h>

class Test_InputInfo: public Test
{
private:
public:
	Test_InputInfo(): Test("INPUTINFO")
	{
	}
	void setup()
	{
		InputInfo info;
		bool failed = false;
		for (int i = 0; i < InputInfo::NUM_KEYS; i++)
		{
			if (info.keys[i] != InputInfo::KEYUP)
				failed = true;
		}
		m_entries.push_back(TestData("Initialization", !failed));
	}	
};	

#endif