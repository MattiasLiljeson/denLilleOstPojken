#ifndef MENUSUBSTATEINTERFACE_H
#define MENUSUBSTATEINTERFACE_H

//#include "MenuSubStateManager.h"

class MenuSubStateManager;

class MenuSubStateInterface
{
public:
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager ) = 0; 
	virtual void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager ) = 0;

};

#endif // MENUSUBSTATEINTERFACE_H