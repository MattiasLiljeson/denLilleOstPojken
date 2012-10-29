#include "ExitSubState.h"

ExitSubState::ExitSubState()
{
}

ExitSubState::~ExitSubState()
{
}

void ExitSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	if( p_currItemIdx == EX_YES)
		p_manager->terminateGame();
	else if( p_currItemIdx == EX_NO)
		p_manager->reqMenuChange(MenuSubStateManager::MENU_MAIN);
}
