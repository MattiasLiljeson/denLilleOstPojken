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
	m_behaviour = NULL;
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
	//m_texts.clear();
	delete m_behaviour;
	m_behaviour = NULL;
}

void MenuSubState::upBtn()
{
	prevSelectableItem();
}

void MenuSubState::downBtn()
{
	nextSelectableItem();
}

void MenuSubState::selectBtn()
{
	if(m_behaviour != NULL)
		m_behaviour->selectBtn( m_currItemIdx, m_manager );
}

void MenuSubState::escBtn()
{	
	if(m_behaviour != NULL)
		m_behaviour->escBtn( m_currItemIdx, m_manager );
}

void MenuSubState::onEntry()
{
	setAllVisible();
}

void MenuSubState::onExit()
{
	setAllNonVisible();
}

void MenuSubState::update( float p_dt )
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->update( p_dt, InputInfo());
}

//void MenuSubState::setTexts( vector<string> p_texts )
//{
//	m_texts = p_texts;
//}
//
//vector<string> MenuSubState::getTexts()
//{
//	return m_texts;
//}

void MenuSubState::setBehaviour( MenuSubStateInterface* p_behaviour )
{
	m_behaviour = p_behaviour;
}

void MenuSubState::setProperties( MenuItemProperties p_properties )
{
	m_properties = p_properties;
}

MenuItemProperties MenuSubState::getProperties()
{
	return m_properties;
}

void MenuSubState::addItems( vector<MenuItem*> p_items )
{
	for( unsigned int i=0; i<p_items.size(); i++ )
	{
		m_items.push_back( p_items[i] );
	}
	setAllNonSelectable();
	setFirstSelectable(); // First item is always "return to main menu"
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