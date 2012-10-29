#include "MenuSubState.h"
#include "MainSubState.h"

MainSubState::MainSubState()
{
}

MainSubState::~MainSubState()
{
}

void MainSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	switch(p_currItemIdx)
	{
	case MM_LEVEL_SELECT:
		p_manager->reqMenuChange( MenuSubStateManager::MENU_LEVEL_SELECT );
		break;
	case MM_HIGHSCORE:
		p_manager->reqMenuChange( MenuSubStateManager::MENU_HIGHSCORE );
		break;
	case MM_CREDITS:
		p_manager->reqMenuChange( MenuSubStateManager::MENU_CREDITS );
		break;
	case MM_EXIT:
		p_manager->reqMenuChange( MenuSubStateManager::MENU_EXIT );
		break;
	default:
		break;
	}
}

void MainSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	p_manager->reqMenuChange( MenuSubStateManager::MENU_EXIT );
}
