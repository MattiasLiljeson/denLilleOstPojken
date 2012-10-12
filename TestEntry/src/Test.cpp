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
	for (unsigned int i = 0; i < m_entries.size(); i++)
	{
		printResult(m_entries[i]);
		cout << endl;
		if (m_entries[i].Result)
			success++;
	}

	string finalResult;
	expandString(finalResult, 39);
	cout << finalResult << "#";
	cout << endl;
	finalResult = "Total Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(m_entries.size());
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;

	finalResult = "Successful Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(success);
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;

	finalResult = "Failed Tests";
	expandString(finalResult, 20);
	finalResult += ": " + toString(m_entries.size() - success);
	expandString(finalResult, 39);
	cout << finalResult << "#" << endl;
	
	for (int i = 0; i < 40; i++)
		cout << "#";

	return TotalTestData(m_entries.size() - success, m_entries.size());
}
void Test::printResult(TestData p_entry)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	string res = p_entry.ID;
	expandString(res, 20);
	res += ": ";

	if (p_entry.Result)
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