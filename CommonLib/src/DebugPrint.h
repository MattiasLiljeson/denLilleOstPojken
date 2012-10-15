#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

// Will only print in debug, will replace call in release with "nothing"
// call like this: DEBUGPRINT(("text"));
#ifdef _DEBUG
	void debugPrint(const char* msg);
	#define DEBUGPRINT(x) debugPrint x
	#ifdef _WIN32
		#include <Windows.h>
		void debugPrint(const char* msg)
		{
			OutputDebugStringA(msg);
		}
	#else
		#include <iostream>
		using namespace std;
		void debugPrint(const char* msg)
		{
			cout<<msg;
		}
	#endif
#else
	#define DEBUGPRINT(x)
#endif



#endif