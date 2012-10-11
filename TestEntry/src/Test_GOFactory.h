#ifndef TESTGOFACTORY_H
#define TESTGOFACTORY_H

#include "Test.h"
#include <GOFactory.h>

class Test_GOFactory: public Test
{
private:
public:
	Test_GOFactory(): Test("GOFACTORY")
	{
	}
	void setup()
	{
		GOFactory factory(NULL);
		Avatar* av = factory.CreateAvatar(NULL, NULL, NULL);
		m_entries.push_back(TestData("Create Avatar", av));
		Monster* mon = factory.CreateMonster(NULL, NULL);
		m_entries.push_back(TestData("Create Monster", mon));
		Pill* pill = factory.CreatePill(NULL, NULL);
		m_entries.push_back(TestData("Create Pill", pill));
	}	
};

#endif