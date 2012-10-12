#ifndef TESTSOUNDINFO_H
#define TESTSOUNDINFO_H

#include "Test.h"
#include <SoundInfo.h>

class Test_SoundInfo: public Test
{
private:
public:
	Test_SoundInfo(): Test("SOUNDINFO")
	{
	}
	void setup()
	{
		SoundInfo info;
		m_entries.push_back(TestData("Construction", info.play == false && info.id == ""));
	}	
};	

#endif