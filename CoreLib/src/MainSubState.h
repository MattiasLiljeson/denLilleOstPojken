#ifndef MAINSUBSTATE_H
#define MAINSUBSTATE_H

#include "MenuSubStateInterface.h"
#include "MenuSubStateManager.h"

class MainSubState : public MenuSubStateInterface
{
public:
	enum { MM_LEVEL_SELECT, MM_HIGHSCORE, MM_CREDITS, MM_EXIT, MM_NUM_ITEMS };

	MainSubState();
	~MainSubState();
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
	virtual void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
};

#endif // MAINSUBSTATE_H
