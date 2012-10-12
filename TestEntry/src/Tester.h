#ifndef TESTER_H
#define TESTER_H

#include "Test.h"
#include "Test_fVector2.h"
#include "Test_fVector3.h"
#include "Test_Circle.h"
#include "Test_Rect.h"
#include "Test_InputInfo.h"
#include "Test_SoundInfo.h"
#include "Test_SoundData.h"
#include "Test_GameStats.h"
#include "Test_MapLoader.h"
#include "Test_GOFactory.h"

// CHANGELOG: 
// 2012-10-12: Jarl and Johan added cout for accumulated failures. 

class Tester
{
private:
public:
	void run();
};

#endif