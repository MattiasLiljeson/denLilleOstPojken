#ifndef TESTSTATES_H
#define TESTSTATES_H

#include "Test.h"
#include <StateManager.h>

class Test_States: public Test
{
private:
public:
	Test_States(): Test("STATES")
	{
	}
	void setup()
	{
		StateManager manager(NULL, NULL);

		newSection("Initialization");
		newEntry(TestData("In-Game State", manager.getInGameState() != NULL));
		newEntry(TestData("Menu State", manager.getMenuState() != NULL));
		newEntry(TestData("Current State", manager.getCurrentState() != NULL));
		newEntry(TestData("Desired State", manager.getCurrentState() == manager.getCurrentState()));

		newSection("Switches");
		manager.requestStateChange(manager.getInGameState());
		newEntry(TestData("New Desired State", manager.getDesiredState() == manager.getInGameState()));
		newEntry(TestData("Same Current State", manager.getCurrentState() != manager.getDesiredState()));
		manager.update(0.5f);
		newEntry(TestData("New Current State", manager.getCurrentState() == manager.getDesiredState()));

		newSection("Invalid States");
		State* outer = new InGameState(&manager, NULL);
		manager.requestStateChange(outer);
		newEntry(TestData("Same Desired State", manager.getDesiredState() != outer));

		newSection("Termination");
		newEntry(TestData("Not Terminated", !manager.isTerminated()));
		manager.terminate();
		newEntry(TestData("Terminated", manager.isTerminated()));

		delete outer;
	}	
};	

#endif