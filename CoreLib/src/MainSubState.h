#ifndef MAINSUBSTATE_H
#define MAINSUBSTATE_H

#include "MenuSubState.h"

class MenuSubStateManager;

class MainSubState : public MenuSubState
{
public:
	enum { MM_LEVEL_SELECT, MM_HIGHSCORE, MM_CREDITS, MM_EXIT, MM_NUM_ITEMS };
	MainSubState( MenuSubStateManager* p_manager );
	~MainSubState();

	virtual void selectBtn();
	virtual void escBtn();
};

#endif // MAINSUBSTATE_H
