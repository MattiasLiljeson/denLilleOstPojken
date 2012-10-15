#ifndef TOSTRING_H
#define TOSTRING_H

#include <sstream>
using namespace std;

// ----------------------
// Useful to-string function
// ----------------------
template <class T>
std::string toString (const T& val)
{
	// Convert input value to string
	// using stringstream
	stringstream strStream;
	strStream << val;
	return strStream.str();
}

#endif