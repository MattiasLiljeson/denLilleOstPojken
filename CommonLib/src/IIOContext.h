#ifndef IIOCONTEXT_H
#define IIOCONTEXT_H

#include "InputInfo.h"

class IIOContext
{
public:
	IIOContext() {}
	virtual ~IIOContext() {}

	InputInfo fetchInput() { return InputInfo(); }
	void draw() {};
private:

};

#endif