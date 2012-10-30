#ifndef MENUSUBSTATEINTERFACE_H
#define MENUSUBSTATEINTERFACE_H

//#include "MenuSubStateManager.h"

class MenuSubStateManager;
class MenuSubState;

class MenuSubStateInterface
{
public:
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu ) = 0; 
	virtual void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu ) = 0;

};

#endif // MENUSUBSTATEINTERFACE_H