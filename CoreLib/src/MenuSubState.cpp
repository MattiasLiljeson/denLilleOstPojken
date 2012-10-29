#include "MenuState.h"
#include "MenuSubState.h"

//=========================================================================
// Private Functions
//=========================================================================
void MenuSubState::nextItem()
{
	if( m_currItemIdx == m_items.size() -1 )
		m_currItemIdx = 0;
	else
		m_currItemIdx++;
}

void MenuSubState::prevItem()
{
	if( m_currItemIdx == 0 )
		m_currItemIdx =  m_items.size()-1;
	else
		m_currItemIdx--;
}

void MenuSubState::nextSelectableItem()
{
	do{
		nextItem();
	} while( !m_items[m_currItemIdx]->isSelectable() );
}

void MenuSubState::prevSelectableItem()
{
	do {
		prevItem();
	} while( !m_items[m_currItemIdx]->isSelectable() );
}

//=========================================================================
// Public Functions
//=========================================================================
MenuSubState::MenuSubState( MenuSubStateManager* p_manager )
{
	m_manager = p_manager;
	m_currItemIdx = 0;

	//std values
	fw = 1.0f/1920.0f;
	fh = 1.0f/1080.0f;

	m_properties.m_firstItemPos	= fVector3( 0.5f, 0.7f, 0.9f );
	m_properties.m_itemSize		= fVector2( fh*600.0f, fh*64.0f );
	m_properties.m_itemTextOffset= fVector2( 0.0f, 0.0f );
	m_properties.m_itemFontSize	= fVector2( fw*32, fh*32 );
	m_properties.m_itemDistance	= 100*fh;
	m_properties.m_itemBackgroundTexturePath = "";

	setAllNonVisible();
}

MenuSubState::~MenuSubState()
{
	clear();
}

void MenuSubState::upBtn()
{
	prevSelectableItem();
}

void MenuSubState::downBtn()
{
	nextSelectableItem();
}

void MenuSubState::escBtn()
{
	m_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
}

void MenuSubState::update( float p_dt )
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->update( p_dt, InputInfo());
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

vector<string> MenuSubState::getTexts()
{
	return m_texts;
}

MenuItemProperties MenuSubState::getProperties()
{
	return m_properties;
}

void MenuSubState::addItems( vector<MenuItem*> p_items )
{
	for( unsigned int i=0; i<m_texts.size(); i++ )
	{
		m_items.push_back( p_items[i] );
	}
	setAllNonSelectable();
	setFirstSelectable(); // First item is always "return to main menu"
}

void MenuSubState::onEntry()
{
	setAllVisible();
}

void MenuSubState::onExit()
{
	setAllNonVisible();
}

void MenuSubState::setFirstSelectable()
{
	m_items.front()->setSelectable(true);
}

void MenuSubState::setAllSelectable()
{
	for( unsigned int i=0; i<m_items.size(); i++ )
		m_items[i]->setSelectable(true);
}

void MenuSubState::setAllNonSelectable()
{
	for( unsigned int i=0; i<m_items.size(); i++ )
		m_items[i]->setSelectable(false);
}

void MenuSubState::setAllVisible()
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->setVisible(true);
}

void MenuSubState::setAllNonVisible()
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->setVisible(false);
}