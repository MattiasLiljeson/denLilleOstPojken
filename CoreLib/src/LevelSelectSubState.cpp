#include "MenuSubState.h"
#include "LevelSelectSubState.h"

LevelSelectSubState::LevelSelectSubState()
{
}

LevelSelectSubState::~LevelSelectSubState()
{
}

void LevelSelectSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	if( p_currItemIdx == LS_MAIN )
	{
		p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
	else
	{
		// Get map idx by removing all static items from item index
		int mapIdx = p_currItemIdx - LS_NUM_ITEMS;
		p_manager->setCurrentMap( mapIdx );
	}
}

void LevelSelectSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
{
	p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
}