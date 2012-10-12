#ifndef TESTER_H
#define TESTER_H


// CHANGELOG: 
// 2012-10-12: Jarl and Johan added cout for accumulated failures.
// 2012-10-12: Jarl and Johan moved includes to Tester.cpp,
// so that we only need to edit Tester.cpp for each new test.

class Tester
{
private:
public:
	void run();
};

#endif