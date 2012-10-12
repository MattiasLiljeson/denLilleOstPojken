#include "Tester.h"

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

	for (unsigned int i = 0; i < tests.size(); i++)
	{
		tests[i]->run();
		cout << endl << endl;
	}

	for (unsigned int i = 0; i < tests.size(); i++)
	{
		delete tests[i];
	}
}
