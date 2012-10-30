#include "MenuSubState.h"
#include "HighscoreSubState.h"

HighscoreSubState::HighscoreSubState()
{
}

HighscoreSubState::~HighscoreSubState()
{
}

void HighscoreSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	if( p_currItemIdx == HS_MAIN )
	{
		p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
}

void HighscoreSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
}