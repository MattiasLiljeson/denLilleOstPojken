#ifndef CREDITSSUBSTATE_H
#define CREDITSSUBSTATE_H

#include "MenuSubState.h"

class MenuSubStateManager;

class CreditsSubState : public MenuSubState
{
public:
	enum { CR_MAIN, CR_NUM_ITEMS };
	CreditsSubState( MenuSubStateManager* p_manager );
	~CreditsSubState();

	virtual void selectBtn();
};

#endif // CreditsSubState_h__
