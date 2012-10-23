#include "MenuSubState.h"

MenuSubState::MenuSubState( vector<MapData> p_maps, int p_type, GOFactory* p_goFactory )
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

	m_maps = p_maps;
	m_currItem = 0;

	m_goFactory = p_goFactory;

	switch(p_type)
	{
		case MENU_MAIN:
			setToMain();
			break;
		case MENU_LEVEL_SELECT:
			setToLevelSelect();
			break;
		case MENU_HIGHSCORE:
			break;
		case MENU_CREDITS:
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
}

void MenuSubState::setToLevelSelect()
{
	m_texts.resize(LS_NUM_ITEMS);
	m_texts[LS_MAIN] = "GO BACK TO MAIN";

	for( unsigned int i=0; i<m_maps.size(); i++ )
	{
		m_texts.push_back(m_maps[i].name);
	}
	// More items, Maps, need more space
	m_firstItemPos.y += 0.3f;
	createItems();
}

void MenuSubState::setToHighscore()
{
	// Not implemented yet
}

void MenuSubState::setToCredits()
{
	// Not implemented yet
}

void MenuSubState::setToExit()
{
	m_texts.resize(EX_NUM_ITEMS);
	m_texts[EX_YES]	= "YES";
	m_texts[EX_NO]	= "NO";

	createItems();
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
}

void MenuSubState::activate()
{
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