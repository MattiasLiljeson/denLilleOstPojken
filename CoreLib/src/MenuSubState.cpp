#include "MenuSubState.h"
#include "StateManager.h"

MenuSubState::MenuSubState( vector<HighScoreItem>* p_highscore, vector<MapData>* p_maps, int p_type, GOFactory* p_goFactory, StateManager* p_stateParent)
{
	//std values
	fw = 1.0f/1920.0f;
	fh = 1.0f/1080.0f;
	m_firstItemPos	= fVector3( 0.5f, 0.5f, 0.9f );
	m_itemSize		= fVector2( fh*600.0f, fh*64.0f );
	m_itemTextOffset= fVector2( 0.0f, 0.0f );
	m_itemFontSize	= fVector2( fw*32, fh*32 );
	m_itemDistance	= 100*fh;
	m_itemBackgroundTexturePath = "";

	m_type = p_type;

	m_maps = p_maps;
	m_highscore = p_highscore;
	m_currItem = 0;

	m_goFactory = p_goFactory;
	m_stateParent = p_stateParent;

	switch(p_type)
	{
		case MENU_MAIN:
			setToMain();
			break;
		case MENU_LEVEL_SELECT:
			setToLevelSelect(m_stateParent->getCommonResources()->unlockedLevels);
			break;
		case MENU_HIGHSCORE:
			setToHighscore();
			break;
		case MENU_CREDITS:
			setToCredits();
			break;
		case MENU_EXIT:
			setToExit();
			break;
	}
}

MenuSubState::~MenuSubState()
{
	clear();
}

void MenuSubState::clear()
{
	for( unsigned int i=0; i<m_items.size(); i++)
	{
		delete m_items[i];
		m_items[i] = NULL;
	}
	m_items.clear();
	m_texts.clear();
}

void MenuSubState::setToMain()
{
	m_texts.resize(MM_NUM_ITEMS);
	m_texts[MM_LEVEL_SELECT]	= "LEVEL SELECT";
	m_texts[MM_HIGHSCORE]		= "HIGHSCORE";
	m_texts[MM_CREDITS]			= "CREDITS";
	m_texts[MM_EXIT]			= "EXIT";

	createItems();
	setAllSelectable();
}

void MenuSubState::setToLevelSelect(int p_size)
{
	m_texts.resize(LS_NUM_ITEMS);
	m_texts[LS_MAIN] = "GO BACK TO MAIN";

	for( int i=0; i< p_size; i++ )
	{
		m_texts.push_back((*m_maps)[i].name);
	}
	// More items, Maps, need more space
	m_firstItemPos.y += 0.3f;
	m_itemDistance *= 0.5f;
	createItems();
	setAllSelectable();
}
void MenuSubState::addLevel()
{
	m_texts.push_back((*m_maps)[m_texts.size()-1].name);
	fVector3 itemPos = m_firstItemPos;
	itemPos.y -= m_itemDistance * m_texts.size();


	m_items.push_back( m_goFactory->createMenuItem( 
		itemPos, m_itemSize, m_texts.back(), m_itemTextOffset, m_itemFontSize,
		m_itemBackgroundTexturePath));
}

void MenuSubState::setToHighscore()
{
	m_texts.resize(HS_NUM_ITEMS);
	m_texts[HS_MAIN] = "GO BACK TO MAIN";

	for( unsigned int i=0; i<m_highscore->size(); i++ )
	{
		stringstream ss;
		ss << (*m_highscore)[i].score;
		m_texts.push_back(ss.str());
	}
	// More items, Maps, need more space
	m_firstItemPos.y += 0.3f;
	//m_itemDistance *= 0.5f;
	createItems();
}

void MenuSubState::setToCredits()
{
	m_texts.resize(CR_NUM_ITEMS);
	m_texts[CR_MAIN] = "GO BACK TO MAIN";

	m_texts.push_back("        CODER OF DESTINY: ANTON ANDERSSON ");
	m_texts.push_back("          EVIL SCIENTIST: ALEXANDER BRODEN");
	m_texts.push_back("BARBARIAN FROM THE NORTH: JOHAN CARLBERG  ");
	m_texts.push_back("      THE VIENNAN ARTIST: JARL LARSSON    ");
	m_texts.push_back("MASTER OF TIME AND SPACE: MATTIAS LILJESON");
	m_texts.push_back("                  MR CEO: ROBIN THUNSTROM ");

	// More items, Names, need more space
	m_firstItemPos.y += 0.3f;
	//m_itemDistance *= 0.5f;
	createItems();
}

void MenuSubState::setToExit()
{
	m_texts.resize(EX_NUM_ITEMS);
	m_texts[EX_YES]	= "YES";
	m_texts[EX_NO]	= "NO";

	createItems();
	setAllSelectable();
}

void MenuSubState::createItems()
{
	fVector3 itemPos = m_firstItemPos;
	for( unsigned int i=0; i<m_texts.size(); i++ )
	{
		itemPos.y -= m_itemDistance;
		m_items.push_back( m_goFactory->createMenuItem( 
			itemPos, m_itemSize, m_texts[i], m_itemTextOffset, m_itemFontSize,
			m_itemBackgroundTexturePath));
	}
	
	setAllUnSelectable();
	// The first item is always selectable as it's the menu item back to 
	// the main menu;
	setFirstSelectable();
}

void MenuSubState::activate()
{
	if (m_type == MENU_LEVEL_SELECT)
	{
		unsigned int numUnlockedLevels =
			(unsigned int)m_stateParent->getCommonResources()->unlockedLevels;
		while (m_texts.size() - 1 < numUnlockedLevels)
		{
			addLevel();
		}
	}
	for( unsigned int i=0; i<m_items.size(); i++)
	{
		m_items[i]->setVisible(true);
	}
}

void MenuSubState::deActivate()
{
	for( unsigned int i=0; i<m_items.size(); i++)
	{
		m_items[i]->setVisible(false);
	}
}

void MenuSubState::setFirstSelectable()
{
	m_items.front()->setSelectable(true);
}

void MenuSubState::setAllSelectable()
{
	for( unsigned int i=0; i<m_items.size(); i++ )
	{
		m_items[i]->setSelectable(true);
	}
}

void MenuSubState::setAllUnSelectable()
{
	for( unsigned int i=0; i<m_items.size(); i++ )
	{
		m_items[i]->setSelectable(false);
	}
}
