#include "Tester.h"
#include "Test.h"
#include "Test_fVector2.h"
#include "Test_fVector3.h"
#include "Test_Circle.h"
#include "Test_Rect.h"
#include "Test_InputInfo.h"
#include "Test_SoundInfo.h"
#include "Test_SoundData.h"
#include "Test_GameStats.h"
#include "Test_MapLoader.h"
#include "Test_GOFactory.h"
#include "Test_GlyphMap.h"

void Tester::run()
{
	vector<Test*> tests;
	tests.push_back(new Test_fVector2());
	tests.push_back(new Test_fVector3());
	tests.push_back(new Test_Circle());
	tests.push_back(new Test_Rect());
	tests.push_back(new Test_InputInfo());
	tests.push_back(new Test_SoundInfo());
	tests.push_back(new Test_SoundData());
	tests.push_back(new Test_GameStats());
	tests.push_back(new Test_GOFactory());
	tests.push_back(new Test_MapLoader());
	tests.push_back(new Test_GlyphMap());

	int totalAmountOfFailures=0;
	int totalAmountOfTestfuncs=0;

	for (unsigned int i = 0; i < tests.size(); i++)
	{
		TotalTestData tdata = tests[i]->run();
		totalAmountOfFailures += tdata.amountOfFailures;
		totalAmountOfTestfuncs += tdata.amountOfTestfuncs;
		cout << endl << endl;
	}

	cout<<"Total failures: "<<totalAmountOfFailures<<"/"<<totalAmountOfTestfuncs<<endl<<endl;

	for (unsigned int i = 0; i < tests.size(); i++)
	{
		delete tests[i];
	}
}
