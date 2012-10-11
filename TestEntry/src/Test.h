#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <sstream>

using namespace std;

struct TestData
{
	string ID;
	bool Result;
	TestData(string p_id, bool p_result)
	{
		ID = p_id;
		Result = p_result;
	}
};

class Test
{
private:
	void expandString(string& p_string, int p_desiredLength);
	string toString(int p_int);
protected:
	string m_name;
	vector<TestData> m_entries;
public:
	Test(string p_name);
	virtual void run();
	virtual void setup() = 0;
	void printResult(TestData p_entry);
};

#endif