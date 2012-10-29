#include "CreditsSubState.h"
#include "MenuSubState.h"

CreditsSubState::CreditsSubState()
{
}

CreditsSubState::~CreditsSubState()
{
}

void CreditsSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	if( p_currItemIdx == CR_MAIN )
	{
		p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
}