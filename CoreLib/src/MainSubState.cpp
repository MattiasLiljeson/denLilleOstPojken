#include "MenuSubState.h"
#include "MainSubState.h"

MainSubState::MainSubState(  MenuSubStateManager* p_manager  )
	: MenuSubState( p_manager )
{
	m_texts.resize(MM_NUM_ITEMS);
	m_texts[MM_LEVEL_SELECT]	= "LEVEL SELECT";
	m_texts[MM_HIGHSCORE]		= "HIGHSCORE";
	m_texts[MM_CREDITS]			= "CREDITS";
	m_texts[MM_EXIT]			= "EXIT";

	createItems();
	setAllSelectable();
}

MainSubState::~MainSubState()
{
}

void MainSubState::selectBtn()
{
	switch(m_currItemIdx)
	{
	case MM_LEVEL_SELECT:
		m_manager->reqMenuChange( MenuSubStateManager::MENU_LEVEL_SELECT );
		break;
	case MM_HIGHSCORE:
		m_manager->reqMenuChange( MenuSubStateManager::MENU_HIGHSCORE );
		break;
	case MM_CREDITS:
		m_manager->reqMenuChange( MenuSubStateManager::MENU_CREDITS );
		break;
	case MM_EXIT:
		m_manager->reqMenuChange( MenuSubStateManager::MENU_EXIT );
		break;
	default:
		break;
	}
}

void MainSubState::escBtn()
{
	m_manager->reqMenuChange( MenuSubStateManager::MENU_EXIT );
}
