#include "MenuState.h"
#include "StateManager.h"

//=========================================================================
// Private Functions
//=========================================================================
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

	int unlocked = m_parent->getCommonResources()->unlockedLevels;

	m_manager->addMenu( m_menuFactory->createMain(), MenuSubStateManager::MENU_MAIN );
	m_manager->addMenu( m_menuFactory->createLevelSelect(m_maps, unlocked), MenuSubStateManager::MENU_LEVEL_SELECT);
	m_manager->addMenu( m_menuFactory->createHighscore(), MenuSubStateManager::MENU_HIGHSCORE );
	m_manager->addMenu( m_menuFactory->createCredits(), MenuSubStateManager::MENU_CREDITS );
	m_manager->addMenu( m_menuFactory->createExit(), MenuSubStateManager::MENU_EXIT );
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
	if(m_io != NULL)
		m_io->clearSpriteInfos();
}


//=========================================================================
// Public Functions
//=========================================================================
MenuState::MenuState( StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps ): State(p_parent)
{
	m_maps = p_maps;
	m_io = p_io;

	m_gof				= NULL;
	m_backgroundMusic	= NULL;
	m_bgItem			= NULL;
	m_menuFactory		= NULL;
	m_manager			= NULL;
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
		{
			if (m_backgroundMusic)
			{
				m_backgroundMusic->deleted = true;
			}
			m_backgroundMusic = new SoundInfo();
			m_backgroundMusic->id = "../Sounds/Music/POL-misty-cave-short.wav";
			m_backgroundMusic->play = true;
			m_backgroundMusic->volume = 20;
			m_io->addSong(m_backgroundMusic);

			createMenus();
			//m_requestedLevel = -1;
			//m_requestedTimer = 0;
		}
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
		{
			if (m_backgroundMusic)
			{
				m_backgroundMusic->deleted = true;
				m_backgroundMusic = NULL;
			}
		}
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

		//Only handle input when no level has been selected
		//if (m_requestedLevel == -1)
		//	handleInput(input);
		//
		//if (m_requestedLevel != -1)
		//{
		//	if (m_requestedTimer > 0.25f)
		//	{
		//		InGameState* inGame = dynamic_cast<InGameState*>(m_parent->getInGameState());
		//		inGame->setCurrentMap(m_requestedLevel);
		//		m_parent->requestStateChange(m_parent->getInGameState());
		//	}
		//	else
		//	{
		//		m_io->fadeSceneToBlack(min(m_requestedTimer*4, 1.0f));
		//	}
		//	m_requestedTimer += p_dt;
		//}
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
