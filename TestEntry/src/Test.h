#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <sstream>

using namespace std;


// CHANGELOG:
// 2012-10-12: Jarl and Johan added return struct for total test stats("TotalTestData"). 

// CHANGELOG:
// 2012-10-12: Anton added support for sections in test data. Useful for separating tests into smaller chunks.

struct TestData
{
	string ID;
	int Result;

	enum
	{
		SUCCESS,
		FAILURE,
		SECTION
	};
	TestData(string p_id, bool p_result)
	{
		ID = p_id;
		Result = p_result ? SUCCESS: FAILURE;
	}
};

struct TotalTestData
{
	TotalTestData(int p_amountOfFailures, int p_totalAmountOfTests)
	{
		amountOfFailures = p_amountOfFailures;
		amountOfTestfuncs = p_totalAmountOfTests;
	}
	int amountOfFailures;
	int amountOfTestfuncs;
};

class Test
{
	static const int WIDTH = 75;
	static const int HASH_COL = WIDTH; 
	static const int COLON_COL = WIDTH - 40;
private:
	void expandString(string& p_string, int p_desiredLength);
	string toString(int p_int);
private:
	string m_name;
	vector<TestData> m_entries;
protected:
	void newSection(string p_id);
	void newEntry(TestData p_entry);
public:
	Test(string p_name);
	virtual TotalTestData run();
	virtual void setup() = 0;
	void printResult(TestData p_entry);
	void printSection(TestData p_entry);
};

#endif