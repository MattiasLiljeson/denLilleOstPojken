#include "MenuSubState.h"
#include "LevelSelectSubState.h"

LevelSelectSubState::LevelSelectSubState()
{
}

LevelSelectSubState::~LevelSelectSubState()
{
}

void LevelSelectSubState::selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	if( p_currItemIdx == LS_MAIN )
	{
		p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
	}
	else
	{
		// Get map idx by removing all static items from item index
		int mapIdx = p_currItemIdx - LS_NUM_ITEMS;
		p_manager->requestMap( mapIdx );
	}
}

void LevelSelectSubState::escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu )
{
	p_menu->setNextMenu( MenuSubStateManager::MENU_MAIN );
}