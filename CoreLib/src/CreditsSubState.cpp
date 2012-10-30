#include "MenuSubState.h"
#include "CreditsSubState.h"

CreditsSubState::CreditsSubState()
{
}

CreditsSubState::~CreditsSubState()
{
}

void CreditsSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	if( p_currItemIdx == CR_MAIN )
	{
		p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
	}
}

void CreditsSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
}