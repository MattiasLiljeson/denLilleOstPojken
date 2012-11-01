#include "MenuSubStateFactory.h"

MenuSubStateFactory::MenuSubStateFactory( GOFactory* p_gof, MenuSubStateManager* p_manager )
{
	m_gof = p_gof;
	m_manager = p_manager;
	m_menuBackSoundPath = "../Sounds/esc.wav";
	m_navigationSoundPath = "../Sounds/nav.wav";
	m_itemSelectSoundPath = "../Sounds/sel.wav";
}

MenuSubStateFactory::~MenuSubStateFactory()
{

}

MenuSubState* MenuSubStateFactory::createMain()
{
	MenuSubState* tmp			= createMenuSubState();
	vector<string> texts		= createMainTexts();
	MenuItemProperties props	= createMainProperties();
	vector<MenuItem*> items		= createItems( props, texts );
	
	float fw = 1.0f/1920.0f;
	float fh = 1.0f/1080.0f;

	// Add logo!
	items.push_back( m_gof->createMenuItem( 
		fVector3( 0.5f, 0.66f, 0.7f ), fVector2( 640.0f*fw, 350.0f*fh ),
		"", fVector2(0.0f, 0.0f),
		fVector2(fw*20, fh*20), "../Textures/default.png" ));

	tmp->addItems( items );
	tmp->setBehaviour( new MainSubState() );
	tmp->setAllSelectable();
	tmp->setSelectable( MainSubState::MM_NUM_ITEMS, false );

	tmp->setMenuBackSnd( m_gof->CreateSoundInfo( m_menuBackSoundPath, 80 ) );
	tmp->setMenuNavigatonSnd( m_gof->CreateSoundInfo( m_navigationSoundPath, 80 ) );
	tmp->setItemSelectSnd( m_gof->CreateSoundInfo( m_itemSelectSoundPath, 80 ) );
	
	return tmp;
}
vector<string> MenuSubStateFactory::createMainTexts()
{
	vector<string> texts;
	texts.resize(MainSubState::MM_NUM_ITEMS);
	texts[MainSubState::MM_LEVEL_SELECT]	= "LEVEL SELECT";
	texts[MainSubState::MM_HIGHSCORE]		= "HIGHSCORE";
	texts[MainSubState::MM_CREDITS]			= "CREDITS";
	texts[MainSubState::MM_EXIT]			= "EXIT";

	return texts;
}
MenuItemProperties MenuSubStateFactory::createMainProperties()
{
	// Make roo m for the logo
	MenuItemProperties properties;
	properties.m_firstItemPos.y -= 0.2f;
	return properties;
}

MenuSubState* MenuSubStateFactory::createLevelSelect( vector<MapData> p_maps, int p_numUnlockedLevels )
{
	MenuSubState* tmp			= createMenuSubState();
	vector<string> texts		= createLevelSelectTexts( p_maps, p_numUnlockedLevels );
	MenuItemProperties props	= createLevelSelectProperties();
	vector<MenuItem*> items		= createItems( props, texts );
	tmp->setBehaviour( new LevelSelectSubState() );
	
	for( int i = LevelSelectSubState::LS_NUM_ITEMS;
		i< LevelSelectSubState::LS_NUM_ITEMS + p_numUnlockedLevels;
		i++ )
	{
		// HACK: break if there are more unlocked levels than maps
		if( (unsigned int) i == items.size())
			break;
		else
			items[i]->setSelectable( true );
	}
	for( unsigned int i = LevelSelectSubState::LS_NUM_ITEMS + p_numUnlockedLevels; i<items.size(); i++ )
		items[i]->setSelectable( false );

	tmp->addItems( items );
	tmp->setSelectable( LevelSelectSubState::LS_PAD, false );

	tmp->setMenuBackSnd( m_gof->CreateSoundInfo( m_menuBackSoundPath, 80 ) );
	tmp->setMenuNavigatonSnd( m_gof->CreateSoundInfo( m_navigationSoundPath, 80 ) );
	tmp->setItemSelectSnd( m_gof->CreateSoundInfo( m_itemSelectSoundPath, 80 ) );
	
	return tmp;
}
vector<string> MenuSubStateFactory::createLevelSelectTexts( vector<MapData> p_maps, int p_numUnlockedLevels )
{
	vector<string> texts;
	texts.resize( LevelSelectSubState::LS_NUM_ITEMS );
	texts[LevelSelectSubState::LS_MAIN] = "GO BACK TO MAIN";

	for( unsigned int i=0; i<p_maps.size(); i++ )
	{
		texts.push_back( p_maps[i].name );
		if((int)i >= p_numUnlockedLevels)
			texts.back() += " (LOCKED)";
	}
	return texts;
}
MenuItemProperties MenuSubStateFactory::createLevelSelectProperties()
{
	// More items, Maps, need more space
	MenuItemProperties properties;
	properties.m_firstItemPos.y += 0.25f;
	properties.m_itemDistance *= 0.5f;
	return properties;
}

MenuSubState* MenuSubStateFactory::createHighscore()
{
	MenuSubState* tmp			= createMenuSubState();
	vector<string> texts		= createHighscoreTexts();
	MenuItemProperties props	= createHighscoreProperties();
	vector<MenuItem*> items		= createItems( props, texts );
	tmp->addItems( items );
	tmp->setBehaviour( new HighscoreSubState() );
	tmp->setAllNonSelectable();
	tmp->setFirstSelectable();

	tmp->setMenuBackSnd( m_gof->CreateSoundInfo( m_menuBackSoundPath, 80 ) );
	tmp->setMenuNavigatonSnd( m_gof->CreateSoundInfo( m_navigationSoundPath, 80 ) );
	tmp->setItemSelectSnd( m_gof->CreateSoundInfo( m_itemSelectSoundPath, 80 ) );
	
	return tmp;
}
vector<string> MenuSubStateFactory::createHighscoreTexts()
{
	vector<string> texts;
	texts.resize(HighscoreSubState::HS_NUM_ITEMS);
	texts[HighscoreSubState::HS_MAIN] = "GO BACK TO MAIN";
	texts.push_back("");

	vector<HighScoreItem> highscores = HighScoreFunctions::readHighScore();
	for( unsigned int i=0; i<highscores.size(); i++ )
	{
		stringstream ss;
		ss << highscores[i].score;
		texts.push_back(ss.str());
	}

	return texts;
}
MenuItemProperties MenuSubStateFactory::createHighscoreProperties()
{
	MenuItemProperties properties;
	//properties.m_firstItemPos.y += 0.1f;
	properties.m_itemDistance *= 0.5f;
	return properties;
}

MenuSubState* MenuSubStateFactory::createCredits()
{
	MenuSubState* tmp			= createMenuSubState();
	vector<string> texts		= createCreditsTexts();
	MenuItemProperties props	= createCreditsProperties();
	vector<MenuItem*> items		= createItems( props, texts );
	tmp->addItems( items );
	tmp->setBehaviour( new CreditsSubState() );
	tmp->setAllNonSelectable();
	tmp->setFirstSelectable();
	
	tmp->setMenuBackSnd( m_gof->CreateSoundInfo( m_menuBackSoundPath, 80 ) );
	tmp->setMenuNavigatonSnd( m_gof->CreateSoundInfo( m_navigationSoundPath, 80 ) );
	tmp->setItemSelectSnd( m_gof->CreateSoundInfo( m_itemSelectSoundPath, 80 ) );
	
	return tmp;
}
vector<string> MenuSubStateFactory::createCreditsTexts()
{
	vector<string> texts;
	texts.resize(CreditsSubState::CR_NUM_ITEMS);
	texts[CreditsSubState::CR_MAIN] = "GO BACK TO MAIN";
	texts.push_back("");
	texts.push_back("DEVELOPERS OF DESTINY:");
	//texts.push_back("-------------------");
	texts.push_back("ANTON ANDERSSON");
	texts.push_back("ALEXANDER BRODEN");
	texts.push_back("JOHAN CARLBERG");
	texts.push_back("JARL LARSSON");
	texts.push_back("MATTIAS LILJESON");
	texts.push_back("ROBIN THUNSTROM");

	return texts;	
}
MenuItemProperties MenuSubStateFactory::createCreditsProperties()
{
	MenuItemProperties properties;
	//properties.m_firstItemPos.y += 0.1f;
	properties.m_itemDistance *= 0.5f;
	return properties;
}

MenuSubState* MenuSubStateFactory::createExit()
{
	MenuSubState* tmp			= createMenuSubState();
	vector<string> texts		= createExitTexts();
	MenuItemProperties props	= createExitProperties();
	vector<MenuItem*> items		= createItems( props, texts );
	tmp->addItems( items );
	tmp->setBehaviour( new ExitSubState() );
	tmp->setAllSelectable();
	tmp->setSelectable( ExitSubState::EX_QUESTION, false );
	tmp->setSelectable( ExitSubState::EX_PAD, false );
	
	tmp->setMenuBackSnd( m_gof->CreateSoundInfo( m_menuBackSoundPath, 80 ) );
	tmp->setMenuNavigatonSnd( m_gof->CreateSoundInfo( m_navigationSoundPath, 80 ) );
	tmp->setItemSelectSnd( m_gof->CreateSoundInfo( m_itemSelectSoundPath, 80 ) );
	
	return tmp;
}
vector<string> MenuSubStateFactory::createExitTexts()
{
	vector<string> texts;
	texts.resize( ExitSubState::EX_NUM_ITEMS );
	texts[ExitSubState::EX_QUESTION]	= "DO YOU REALLY WANT TO QUIT ?";
	texts[ExitSubState::EX_YES]	= "YES";
	texts[ExitSubState::EX_NO]	= "NO";

	return texts;
}
MenuItemProperties MenuSubStateFactory::createExitProperties()
{
	MenuItemProperties properties;
	properties.m_firstItemPos.y -= 0.1f;
	properties.m_itemDistance *= 0.5f;
	return properties;
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

MenuSubState* MenuSubStateFactory::createMenuSubState()
{
	return new MenuSubState( m_manager );
}
