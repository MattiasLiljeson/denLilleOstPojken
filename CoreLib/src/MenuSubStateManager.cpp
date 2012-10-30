#include "MenuSubStateManager.h"

MenuSubStateManager::MenuSubStateManager( MenuState* p_parent )
{
	m_menus.resize( NUM_MENUS );
	for( unsigned int i=0; i<m_menus.size(); i++ )
		m_menus[i] = NULL;

	m_parent = p_parent;
	m_currMenu = 0;
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
	if( m_menus[p_menu] != NULL)
	{
		m_menus[m_currMenu]->onExit();
		m_currMenu = p_menu;
		m_menus[m_currMenu]->onEntry();
	}
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
}

void MenuSubStateManager::addMenu( MenuSubState* p_menu, Menu p_type )
{
	if( p_menu != NULL)
	{
		m_menus[p_type] = p_menu;
	
		if( p_type == MENU_MAIN)
			m_menus[p_type]->setAllVisible();
		else
			m_menus[p_type]->setAllNonVisible();
	}
}

void MenuSubStateManager::update( float p_dt )
{
	for( unsigned int i=0; i<m_menus.size(); i++ )
		if( m_menus[i] != NULL)
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
