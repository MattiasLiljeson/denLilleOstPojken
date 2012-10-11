#ifndef TESTSOUNDDATA_H
#define TESTSOUNDDATA_H

#include "Test.h"
#include <SoundInfo.h>

class Test_SoundData: public Test
{
private:
public:
	Test_SoundData(): Test("SOUNDDATA")
	{
	}
	void setup()
	{
		SoundData data;
		m_entries.push_back(TestData("Construction", data.path == ""));
	}	
};	

#endif