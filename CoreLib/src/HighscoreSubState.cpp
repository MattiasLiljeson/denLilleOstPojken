#include "MenuSubState.h"
#include "HighscoreSubState.h"

HighscoreSubState::HighscoreSubState()
{
}

HighscoreSubState::~HighscoreSubState()
{
}

void HighscoreSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	if( p_currItemIdx == HS_MAIN )
	{
		p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
	}
}

void HighscoreSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
}