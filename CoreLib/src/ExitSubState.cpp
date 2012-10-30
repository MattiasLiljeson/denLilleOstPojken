#include "MenuSubState.h"
#include "ExitSubState.h"

ExitSubState::ExitSubState()
{
}

ExitSubState::~ExitSubState()
{
}

void ExitSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	if( p_currItemIdx == EX_YES)
		p_manager->terminateGame();
	else if( p_currItemIdx == EX_NO)
		p_menu->setNextMenu(MenuSubStateManager::MENU_MAIN);
}

void ExitSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
}