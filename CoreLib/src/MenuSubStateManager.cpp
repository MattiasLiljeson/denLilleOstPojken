#include "MenuSubStateManager.h"

MenuSubStateManager::MenuSubStateManager( MenuState* p_parent )
{
	m_menus.resize( NUM_MENUS );
}

MenuSubStateManager::~MenuSubStateManager()
{
	for( unsigned int menuIdx=0; menuIdx<m_menus.size(); menuIdx++ )
	{
		delete m_menus[menuIdx];
		m_menus[menuIdx] = NULL;
	}
}

void MenuSubStateManager::reqMenuChange( int p_menu )
{
	m_menus[m_currMenu]->onExit();
	m_currMenu = p_menu;
	m_menus[m_currMenu]->onEntry();
}

void MenuSubStateManager::handleInput(InputInfo p_input)
{
	if( p_input.keys[InputInfo::UP] == InputInfo::KEYPRESSED ||
		p_input.keys[InputInfo::W_KEY] == InputInfo::KEYPRESSED )
		m_menus[m_currMenu]->upBtn();

	if( p_input.keys[InputInfo::DOWN] == InputInfo::KEYPRESSED ||
		p_input.keys[InputInfo::S_KEY] == InputInfo::KEYPRESSED )
		m_menus[m_currMenu]->downBtn();

	if( p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED ||
		p_input.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED )
		m_menus[m_currMenu]->selectBtn();

	if( p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED )
		m_menus[m_currMenu]->escBtn();

	// || !m_io->isRunning()
}

void MenuSubStateManager::addMenu( MenuSubState* p_menu, int p_type )
{
	m_menus[p_type] = p_menu;
}

void MenuSubStateManager::update( float p_dt )
{
	for( unsigned int i=0; i<m_menus.size(); i++ )
		m_menus[i]->update( p_dt );
}

void MenuSubStateManager::terminateGame()
{
	m_parent->getParent()->terminate();
}

void MenuSubStateManager::setCurrentMap( int p_mapIdx )
{
	InGameState* inGame = dynamic_cast<InGameState*>(m_parent->getParent()->getInGameState());
	inGame->setCurrentMap(p_mapIdx);
	m_parent->getParent()->requestStateChange(m_parent->getParent()->getInGameState());
}
