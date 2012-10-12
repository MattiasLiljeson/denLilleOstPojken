#ifndef TESTAVATAR_H
#define TESTAVATAR_H

#include "Test.h"
#include <Avatar.h>

class Test_Avatar: public Test
{
private:
public:
	Test_Avatar(): Test("AVATAR")
	{
	}
	void setup()
	{
		//Testing a null based avatar
		Avatar avatar(NULL, NULL, NULL, NULL);
		m_entries.push_back(TestData("Null Tile", avatar.getCurrentTile() == NULL));
		m_entries.push_back(TestData("Not Moving", avatar.getDirection() == Direction::NONE));
		m_entries.push_back(TestData("Not Moving", avatar.getTileInterpolationFactor() == 0));

		InputInfo inf;
		avatar.update(0.5f, inf);

		float dt = avatar.getTileInterpolationFactor();
		m_entries.push_back(TestData("Time Interval", dt <= 1 && dt >= 0));


		//Testing a typical avatar
		

	}	
};	

#endif