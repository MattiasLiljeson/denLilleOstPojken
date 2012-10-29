#include "MenuSubState.h"
#include "LevelSelectSubState.h"

LevelSelectSubState::LevelSelectSubState( MenuSubStateManager* p_manager,
	vector<MapData> p_maps )
	: MenuSubState( p_manager )
{
	m_maps = p_maps;
	m_texts.resize( LS_NUM_ITEMS );
	m_texts[LS_MAIN] = "GO BACK TO MAIN";

	for( unsigned int i=0; i<m_maps.size(); i++ )
	{
		m_texts.push_back( m_maps[i].name );
	}
	// More items, Maps, need more space
	m_properties.m_firstItemPos.y += 0.3f;
	m_properties.m_itemDistance *= 0.5f;
}

LevelSelectSubState::~LevelSelectSubState()
{
}

void LevelSelectSubState::selectBtn()
{
	if( m_currItemIdx == LS_MAIN )
	{
		m_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
	else
	{
		// Get map idx by removing all static items from item index
		int mapIdx = m_currItemIdx - LS_NUM_ITEMS;
		m_manager->setCurrentMap( mapIdx );
	}
}
