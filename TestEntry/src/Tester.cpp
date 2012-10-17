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
#include "Test_Avatar.h"
#include "Test_Tile.h"
#include "Test_Tilemap.h"
#include "Test_Monster.h"
#include "Test_States.h"
#include "Test_Pill.h"
#include "Test_SuperPill.h"
#include "Test_SpeedPill.h"
#include "Test_Bomb.h"
#include "Test_BombPill.h"

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
	tests.push_back(new Test_Avatar());
	tests.push_back(new Test_Tile());
	tests.push_back(new Test_Tilemap());
	tests.push_back(new Test_Monster());
	tests.push_back(new Test_States());
	tests.push_back(new Test_Pill());
	tests.push_back(new Test_SuperPill());
	tests.push_back(new Test_SpeedPill());
	tests.push_back(new Test_Bomb());
	tests.push_back(new Test_BombPill());

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
