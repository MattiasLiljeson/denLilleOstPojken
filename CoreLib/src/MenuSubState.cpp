#include "MenuState.h"
#include "MenuSubState.h"
#include "StateManager.h"

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
	m_currState = IN_ENTRY;
	m_nextMenu = 0;
	m_stateTimer = 0.0f;
	m_behaviour = NULL;
	m_introTime = 0.1f;
	m_outroTime = 0.1f;
	m_selectedTime = 0.1f;
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
		m_behaviour->selectBtn( m_currItemIdx, m_manager, this );
}

void MenuSubState::escBtn()
{	
	if(m_behaviour != NULL)
		m_behaviour->escBtn( m_currItemIdx, m_manager, this );
}

void MenuSubState::onEntry()
{
	setAllVisible();
	m_currState = IN_ENTRY;
	m_stateTimer = 0.0f;
	m_nextMenu = 0;

	for( unsigned int i=0; i<m_items.size(); i++)
	{
		if( m_items[i] != NULL )
			m_items[i]->resetAnimation(IN_ENTRY);
	}
}

void MenuSubState::onExit()
{
	setAllNonVisible();
}

void MenuSubState::update( float p_dt )
{
	m_stateTimer += p_dt;

	for( unsigned int i=0; i<m_items.size(); i++)
	{
		if( m_items[i] != NULL )
			m_items[i]->update( p_dt, InputInfo());
	}

	switch( m_currState )
	{
	case IN_ENTRY:
		updateInEntry( p_dt );
		break;
	case IN_MENU:
		updateInMenu( p_dt );
		break;
	case ITEM_SELECTED:
		updateItemSelected( p_dt );
		break;
	case IN_EXIT:
		updateInExit( p_dt );
		break;
	}
}

void MenuSubState::updateInEntry( float p_dt )
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->animateText( 0.02f, 2.0f, m_introTime, m_currState);

	if(m_stateTimer > m_introTime)
	{
		m_currState = IN_MENU;
		m_stateTimer = 0.0f;
	}
	else
	{
		// do something
	}
}
void MenuSubState::updateInMenu( float p_dt )
{
	if( (unsigned int)m_currItemIdx < m_items.size() )
		m_items[m_currItemIdx]->animateText( 0.02f, 2.0f, 15.0f, m_currState);
}

void MenuSubState::updateItemSelected( float p_dt )
{
	if( (unsigned int)m_currItemIdx < m_items.size() )
		m_items[m_currItemIdx]->animateText( 0.02f, 2.0f, 150.0f, m_currState);
	
	if(m_stateTimer > m_selectedTime)
	{
		m_currState = IN_EXIT;
	}
}

void MenuSubState::updateInExit( float p_dt )
{
	for( unsigned int i=0; i<m_items.size(); i++)
		m_items[i]->animateText( 0.02f, 2.0f, m_outroTime, m_currState);

	if(m_stateTimer > m_outroTime)
	{
		m_manager->reqMenuChange( m_nextMenu );
		m_stateTimer = 0.0f;
	}
	else
	{
		// do something
	}
}

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
}

void MenuSubState::setNextMenu( int p_menu )
{
	m_nextMenu = p_menu;
	setItemSelected();
}

void MenuSubState::setItemSelected()
{
	m_currState = ITEM_SELECTED;
	m_stateTimer = 0.0f;	

	if( m_items[m_currItemIdx] != NULL )
		m_items[m_currItemIdx]->resetAnimation(ITEM_SELECTED);
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
