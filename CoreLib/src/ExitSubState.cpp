#include "ExitSubState.h"

ExitSubState::ExitSubState( MenuSubStateManager* p_manager )
	: MenuSubState( p_manager )
{
	m_texts.resize( EX_NUM_ITEMS );
	m_texts[EX_YES]	= "YES";
	m_texts[EX_NO]	= "NO";
}

ExitSubState::~ExitSubState()
{
}

void ExitSubState::selectBtn( int p_curritemIdx, MenuSubStateManager* p_manager )
{
	if( m_currItemIdx == EX_YES)
		m_manager->terminateGame();
	else if( m_currItemIdx == EX_NO)
		m_manager->reqMenuChange(MenuSubStateManager::MENU_MAIN);
}
