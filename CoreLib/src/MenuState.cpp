#include "MenuState.h"
#include "StateManager.h"

//=========================================================================
// Private Functions
//=========================================================================
//void MenuState::resetItemOffset( int p_idx )
//{
//	if(m_currMenu < m_menus.size() && p_idx < m_menus[m_currMenu]->m_items.size())
//		m_menus[m_currMenu]->m_items[p_idx]->setTextOffset(0.0f, 0.0f);
//}

bool MenuState::playSound()
{
	if( m_itemSelectSnd != NULL )
	{
		m_itemSelectSnd->play = true;
		return true;
	}
	else
	{
		return false;
	}
}

void MenuState::createMenus()
{
	m_io->clearSpriteInfos();
	m_gof = new GOFactory(m_io);
	m_manager = new MenuSubStateManager(this);
	m_menuFactory = new MenuSubStateFactory(m_gof, m_manager);

	float fw = 1.0f/1920.0f;
	float fh = 1.0f/1080.0f;
	m_bgItem = m_gof->createMenuItem( 
		fVector3( 0.5f, 0.5f, 0.5f ), fVector2( 1.0f, 1.0f ),
		"COPYRIGHT 2012 MAJESTIC 12", fVector2(0.0f, -fh*500.0f),
		fVector2(fw*20, fh*20), "../Textures/SplashScreen.png" );

	m_manager->addMenu( m_menuFactory->createMain(), MenuSubStateManager::MENU_MAIN );
	m_manager->addMenu( m_menuFactory->createLevelSelect(m_maps), MenuSubStateManager::MENU_LEVEL_SELECT );
	m_manager->addMenu( m_menuFactory->createHighscore(), MenuSubStateManager::MENU_HIGHSCORE );
	m_manager->addMenu( m_menuFactory->createCredits(), MenuSubStateManager::MENU_CREDITS );
	m_manager->addMenu( m_menuFactory->createExit(), MenuSubStateManager::MENU_EXIT );

	m_itemSelectSnd = m_gof->CreateSoundInfo( "../Sounds/Plink_08.wav", 80 );
}


void MenuState::removeMenus()
{
	delete m_bgItem;
	m_bgItem = NULL;
	delete m_menuFactory;
	m_menuFactory = NULL;
	delete m_manager;
	m_manager = NULL;
	delete m_gof;
	m_gof = NULL;
	m_io->clearSpriteInfos();
}


//=========================================================================
// Public Functions
//=========================================================================
MenuState::MenuState( StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps ): State(p_parent)
{
	m_maps = p_maps;
	m_io = p_io;
	m_gof = NULL;
	m_itemSelectSnd = NULL;
}

MenuState::~MenuState()
{
	onExit();
}

bool MenuState::onEntry()
{
	// Only allocate if not allocated already
	if (!m_resourcesAllocated)
	{
		if (m_io)
			createMenus();
		m_resourcesAllocated = true;
	}
	return true;
}

bool MenuState::onExit()
{
	// Only deallocate if allocated
	if (m_resourcesAllocated)
	{
		if (m_io)
			removeMenus();
		m_resourcesAllocated = false;
	}
	return true;
}

void MenuState::update( float p_dt )
{	
	m_manager->update( p_dt );

	if( m_io )
	{
		InputInfo input = m_io->fetchInput();

		// NOTE: This function has to the last function called in update.
		// (may trigger state-change and sprite dealloc)
		handleInput(input);
	}

}
void MenuState::draw(float p_dt)
{
}

void MenuState::handleInput(InputInfo p_input)
{
	m_manager->handleInput( p_input );
}

StateManager* MenuState::getParent()
{
	return m_parent;
}
