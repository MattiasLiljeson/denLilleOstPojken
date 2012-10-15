#include "Test.h"

Test::Test(string p_name)
{
	m_name = p_name;
}
string Test::toString(int p_int)
{
	stringstream ss;
	ss << p_int;
	return ss.str();
}

void Test::expandString(string& p_string, int p_desiredLength)
{
	while (p_string.size() < p_desiredLength)
		p_string += " ";
}

void Test::newSection(string p_id)
{
	m_entries.push_back(TestData(p_id, true));
	m_entries.back().Result = TestData::SECTION;
}

void Test::newEntry(TestData p_entry)
{
	m_entries.push_back(p_entry);
}

TotalTestData Test::run()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	setup();

	for (int i = 0; i < 40; i++)
		cout << "#";
	cout << endl;
	string s = "Running test";
	expandString(s, 20);
	s += ": " + m_name;
	expandString(s, 39);
	cout << s << "#";
	cout << endl;

	int success = 0;
	int total = 0;
	for (unsigned int i = 0; i < m_entries.size(); i++)
	{
		if (m_entries[i].Result != TestData::SECTION)
		{
			printResult(m_entries[i]);
			total++;
			if (m_entries[i].Result == TestData::SUCCESS)
				success++;
		}
		else
		{
			printSection(m_entries[i]);
		}
		cout << endl;
	}

	string finalResult;
	expandString(finalResult, 39);
	cout << finalResult << "#";
	cout << endl;
	finalResult = "Total Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(total);
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;

	finalResult = "Successful Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(success);
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;

	finalResult = "Failed Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(total - success);
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;
	
	for (int i = 0; i < 40; i++)
		cout << "#";

	return TotalTestData(total - success, total);
}
void Test::printResult(TestData p_entry)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	string res = p_entry.ID;
	expandString(res, 20);
	res += ": ";

	if (p_entry.Result == TestData::SUCCESS)
	{
		SetConsoleTextAttribute(hConsole, 10);
		res += "SUCCEEDED";
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		res += "FAILED"; 
	}
	expandString(res, 39);
	cout << res;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "#";
}
void Test::printSection(TestData p_entry)
{
	string s;
	expandString(s, 39);
	s += "#\n";
	cout << s;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 5);

	string res = "Section";
	expandString(res, 20);
	res += ": " + p_entry.ID;
	expandString(res, 39);
	cout << res;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "#";
}