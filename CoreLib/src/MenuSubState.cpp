#include "MenuSubState.h"

MenuSubState::MenuSubState( int p_type, GOFactory* p_goFactory )
{
	// HACK: hard coded values used to set positions of elements according to
	// fullHD resolution
	fw = 1.0f/1920.0f;
	fh = 1.0f/1080.0f;


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

	for(int i=0; i<MM_NUM_ITEMS ; i++ )
	{
		m_items.push_back( m_goFactory->createMenuItem( 
			fVector3( 0.5f, 0.5f - i*fh*100.0f, 0.9f ), fVector2( fh*600.0f, fh*64.0f ),
			m_texts[i], fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"" ));
	}
}

void MenuSubState::setToLevelSelect()
{
	m_texts.resize(LS_NUM_ITEMS);
	m_texts[LS_MAIN]		= "GO BACK TO MAIN";
	m_texts[LS_START_LEVEL]	= "START LEVEL";

	for(int i=0; i<LS_NUM_ITEMS ; i++ )
	{
		m_items.push_back( m_goFactory->createMenuItem( 
			fVector3( 0.5f, 0.5f - i*fh*100.0f, 0.9f ), fVector2( fh*600.0f, fh*64.0f ),
			m_texts[i], fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"" ));
	}
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

	for(int i=0; i<EX_NUM_ITEMS ; i++ )
	{
		m_items.push_back( m_goFactory->createMenuItem( 
			fVector3( 0.5f, 0.5f - i*fh*100.0f, 0.9f ), fVector2( fh*600.0f, fh*64.0f ),
			m_texts[i], fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"" ));
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