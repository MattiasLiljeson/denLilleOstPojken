#include <iostream>
#include "Tester.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Tester t;
	t.run();

	cin.get();
	return 0;
}