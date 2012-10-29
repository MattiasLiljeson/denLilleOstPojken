#include "MenuSubStateFactory.h"

MenuSubStateFactory::MenuSubStateFactory( GOFactory* p_gof, MenuSubStateManager* p_manager )
{
	m_gof = p_gof;
	m_manager = p_manager;
}

MenuSubStateFactory::~MenuSubStateFactory()
{

}

MenuSubState* MenuSubStateFactory::createMain()
{
	MenuSubState* tmp = new MainSubState( m_manager );
	initMenu( tmp );
	return tmp;
}

MenuSubState* MenuSubStateFactory::createLevelSelect( vector<MapData> p_maps )
{
	MenuSubState* tmp = new LevelSelectSubState( m_manager, p_maps);
	initMenu( tmp );
	return tmp;
}

MenuSubState* MenuSubStateFactory::createHighscore()
{
	MenuSubState* tmp = new HighscoreSubState( m_manager );
	initMenu( tmp );
	return tmp;
}

MenuSubState* MenuSubStateFactory::createCredits()
{
	MenuSubState* tmp = new CreditsSubState( m_manager );
	initMenu( tmp );
	return tmp;
}

MenuSubState* MenuSubStateFactory::createExit()
{
	MenuSubState* tmp = new ExitSubState( m_manager );
	initMenu( tmp );
	return tmp;
}

void MenuSubStateFactory::initMenu( MenuSubState* p_menu )
{
	vector<string> texts = p_menu->getTexts();
	MenuItemProperties props = p_menu->getProperties();
	vector<MenuItem*> items = createItems(props, texts);
	p_menu->addItems(items);
}

vector<MenuItem*> MenuSubStateFactory::createItems( MenuItemProperties p_properties,
	vector<string> p_texts)
{
	vector<MenuItem*> items;
	fVector3 itemPos = p_properties.m_firstItemPos;
	for( unsigned int i=0; i<p_texts.size(); i++ )
	{
		itemPos.y -= p_properties.m_itemDistance;
		items.push_back( m_gof->createMenuItem( 
			itemPos,
			p_properties.m_itemSize,
			p_texts[i], p_properties.m_itemTextOffset,
			p_properties.m_itemFontSize,
			p_properties.m_itemBackgroundTexturePath
			));
	}

	return items;
}
