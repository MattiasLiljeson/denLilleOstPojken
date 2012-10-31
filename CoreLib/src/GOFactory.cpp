#include "GOFactory.h"

GOFactory::GOFactory(IODevice* p_io)
{
	m_io = p_io;
	m_tileMapFactory = new TMFactory(m_io,this);
}
GOFactory::~GOFactory()
{
	delete m_tileMapFactory;
}

Avatar* GOFactory::CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats)
{
	fVector3 pos = GetCenter(p_startTile, 0.5f); 
	fVector2 size = GetScaledSize(p_startTile, 2.0f);

	Rect r;
	r.x		= 0;
	r.y		= 0;
	r.width = 64;
	r.height = 64;
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/player.png",
		pos, size, &r);
	SpriteInfo* shadow = CreateSpriteInfo("../Textures/playerShadow.png",
		pos, size, &r);
	return new Avatar(spriteInfo, shadow, p_map, p_startTile, p_stats, CreateSoundInfo("../Sounds/avatar_killed.wav",100), CreateSoundInfo("../Sounds/jump.wav",100));
}
Monster* GOFactory::CreateMonster(Tile* p_tile, Tilemap* p_map, GameStats* p_stats, int p_type)
{
	fVector3 pos = GetCenter(p_tile, 0.2f); 
	fVector2 size = GetScaledSize(p_tile, 2.0f);

	std::string spriteInfoPath;
	int type = p_type - (TileTypes::ENEMIESPAWN-30);
	if(type == 1)
		spriteInfoPath = "../Textures/rat.png";
	else if(type == 2)
		spriteInfoPath = "../Textures/rat2.png";

	SpriteInfo* spriteInfo = CreateSpriteInfo( spriteInfoPath,
		pos, size, NULL);
	if(type == 1)
		return new Rat(p_stats, spriteInfo, p_tile, p_map, CreateSoundInfo("../Sounds/monster_killed_v2.wav",100));
	else if(type == 2)
		return new InfectedRat(p_stats, spriteInfo, p_tile, p_map, CreateSoundInfo("../Sounds/monster_killed_v2.wav",100));

	return NULL;
}

Trap* GOFactory::CreateTrap(Tile* p_tile, Tilemap* p_map)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 2.0f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Trap_Spikes.png",
		pos, size, NULL);
	return new Trap(spriteInfo, p_tile, p_map);
}

SuperPill* GOFactory::CreateSuperPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.19f); 
	fVector2 size = GetScaledSize(p_tile, 1.5f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Item_SuperCheesy.png",
		pos, size, NULL);
	return new SuperPill(spriteInfo, p_tile, p_gameStats, CreateSoundInfo("../Sounds/use_power-up.wav",100));
}
SpeedPill* GOFactory::CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 1.3f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/speedpowerup.png",
		pos, size, NULL);

	pos = GetCenter(p_tile, 0.12f); 
	size = GetScaledSize(p_tile, 1.5f);
	SpriteInfo* containerSpriteInfo = CreateSpriteInfo("../Textures/buff_ball.png",
		pos, size, NULL);	
	
	pos = GetCenter(p_tile, 0.11f); 
	SpriteInfo* containerShadowSpriteInfo = CreateSpriteInfo("../Textures/buff_ball_caustic.png",
		pos, size, NULL);

	CollectableContainer* container = new CollectableContainer(containerSpriteInfo,containerShadowSpriteInfo);

	return new SpeedPill(spriteInfo, p_tile, p_gameStats, container, CreateSoundInfo("../Sounds/use_power-up.wav",100));
}
Pill* GOFactory::CreatePill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Pill_32.png",
		pos, size, NULL);
	
	return new Pill(spriteInfo, CreateSoundInfo("../Sounds/new_eat_pill_DRIP.wav",100), p_tile, p_gameStats);
}
BombPill* GOFactory::CreateBombPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 1.2f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/bombitem.png",
		pos, size, NULL);

	pos = GetCenter(p_tile, 0.12f); 
	size = GetScaledSize(p_tile, 1.5f);
	SpriteInfo* containerSpriteInfo = CreateSpriteInfo("../Textures/item_box.png",
		pos, size, NULL);	

	pos = GetCenter(p_tile, 0.11f); 
	SpriteInfo* containerShadowSpriteInfo = CreateSpriteInfo("../Textures/item_box_caustic.png",
		pos, size, NULL);

	CollectableContainer* container = new CollectableContainer(containerSpriteInfo,containerShadowSpriteInfo);

	return new BombPill(spriteInfo, p_tile, p_gameStats, container ,CreateSoundInfo("../Sounds/GunCock.wav",100));

}
Bomb* GOFactory::CreateBomb(Tile* p_tile, Tilemap* p_map)
{
	vector<pair<Tile*, SpriteInfo*> > flames;

	fVector3 pos = GetCenter(p_tile, 0.6f); 
	fVector2 size = GetScaledSize(p_tile, 1.2f);
	Rect r;
	r.x = 0;
	r.y = 0;
	r.height = 64;
	r.width = 64;
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Explosion_Animation.png",
		pos, size, &r);
	flames.push_back(pair<Tile*, SpriteInfo*>(p_tile, spriteInfo));

	TilePosition dir[] = {TilePosition(1, 0), TilePosition(-1, 0), TilePosition(0, 1), TilePosition(0, -1)};
	for (int i = 0; i < 4; i++)
	{
		Tile* curr = p_map->getTile(p_tile->getTilePosition() + dir[i]);
		while (curr && curr->isFree())
		{
			pos = GetCenter(curr, 0.6f); 
			size = GetScaledSize(curr, 1.2f);

			r.x = 0;
			r.y = 0;
			r.height = 64;
			r.width = 64;
			SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Explosion_Animation.png",
				pos, size, &r);

			flames.push_back(pair<Tile*, SpriteInfo*>(curr, spriteInfo));
			curr = p_map->getTile(curr->getTilePosition() + dir[i]);
		}
	}

	pos = GetCenter(p_tile, 0.19f); 
	size = GetScaledSize(p_tile, 2.0f);

	Rect br;
	br.x = 0;
	br.y = 0;
	br.height = 64;
	br.width = 64;
	spriteInfo = CreateSpriteInfo("../Textures/bombitem_anim.png",
		pos, size, &br);

	return new Bomb(spriteInfo, flames, p_tile, p_map, CreateSoundInfo("../Sounds/Click.wav",100), CreateSoundInfo("../Sounds/blast_2.wav",100));
}

Tilemap* GOFactory::CreateTileMap(int p_theme, int p_width, int p_height, vector<int> p_mapData)
{
	return m_tileMapFactory->CreateTileMap(p_theme, p_width,p_height,p_mapData);
}
Tile* GOFactory::CreateTile(bool p_type, TilePosition p_position, float p_width,
	float p_height)
{
	fVector3 pos = fVector3(p_position.x * p_width + p_width * 0.5f,
		p_position.y * p_height + p_height * 0.5f, 0.0f);
	fVector2 size = fVector2(p_width, p_height);
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/wall.png",
		pos, size, NULL);

	if (spriteInfo)
		spriteInfo->visible = !p_type;

	return new Tile(p_type, p_position, p_width, p_height, spriteInfo);
}
Switch* GOFactory::CreateSwitch(Tile* p_tile, GameStats* p_gameStats, 
	vector<WallSwitch*> p_targets, int p_type)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 1.7f);

	int yOffset = (p_type - (TileTypes::PATHS+1))*64;

	Rect r;
	r.x = 0;
	r.y = yOffset;
	r.width = 64;
	r.height = 64;

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Switch_Tileset.png",
		pos, size, &r);
	return new Switch(spriteInfo, p_tile, p_gameStats, p_targets, CreateSoundInfo("../Sounds/switch.wav",100));
}

WallSwitch* GOFactory::CreateWallSwitch(Tile* p_tile, int p_type)
{	
	fVector3 pos = GetCenter(p_tile,0.1f);
	fVector2 size = GetScaledSize(p_tile,2.0f);

	int yOffset = (p_type - (TileTypes::SWITCHES+1))*64;

	Rect r;
	r.x = 0;
	r.y = yOffset;
	r.height = 64;
	r.width = 64;

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Blockade_Tileset.png",
		pos,size,&r);

	return new WallSwitch(spriteInfo,p_tile);
}

SpriteInfo* GOFactory::CreateSpriteInfo(string p_texture, fVector3 p_position,
	fVector2 p_size, Rect* p_sourceRect)
{
	if (!m_io)
		return NULL;
	SpriteInfo* spriteInfo = new SpriteInfo;
	spriteInfo->transformInfo.translation[TransformInfo::X] = p_position.x;
	spriteInfo->transformInfo.translation[TransformInfo::Y] = p_position.y;
	spriteInfo->transformInfo.translation[TransformInfo::Z] = p_position.z;
	spriteInfo->transformInfo.scale[TransformInfo::X] = p_size.x;
	spriteInfo->transformInfo.scale[TransformInfo::Y] = p_size.y;
	spriteInfo->textureFilePath = p_texture;

	m_io->addSpriteInfo(spriteInfo);
	if (p_sourceRect)
	{
		spriteInfo->textureRect.x		= p_sourceRect->x;
		spriteInfo->textureRect.y		= p_sourceRect->y;
		spriteInfo->textureRect.width = p_sourceRect->width;
		spriteInfo->textureRect.height = p_sourceRect->height;
	}
	return spriteInfo;
}
fVector3 GOFactory::GetCenter(Tile* p_tile, float p_depth)
{
	if (p_tile)
	{
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		TilePosition tp = p_tile->getTilePosition();

		return fVector3(tp.x * w + w * 0.5f, tp.y * h + h * 0.5f, p_depth);
	}
	return fVector3(0, 0, 0);
}
fVector2 GOFactory::GetScaledSize(Tile* p_tile, float p_scale)
{
	if (p_tile)
	{
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		TilePosition tp = p_tile->getTilePosition();

		return fVector2(w * p_scale, h * p_scale);
	}
	return fVector2(0, 0);
}

SoundInfo* GOFactory::CreateSoundInfo(string p_sound, int p_volume)
{
	if (m_io)
	{
		SoundInfo* soundInfo = new SoundInfo();
		soundInfo->play = false;
		soundInfo->id = p_sound;
		soundInfo->volume = (float)p_volume;
		m_io->addSound(soundInfo);
		return soundInfo;
	}
	return NULL;
}

MenuItem* GOFactory::createMenuItem( fVector3 p_position, fVector2 p_size,
	string p_text, fVector2 p_textOffset, fVector2 p_fontSize, string p_bgTexPath)
{
	float scrW = GAME_FAIL;
	float scrH = GAME_FAIL;
	if(m_io != NULL)
	{
		scrW = (float)m_io->getScreenWidth();
		scrH = (float)m_io->getScreenHeight();
	}

	fVector2 finalPos, finalTextOffset;
	finalPos.x = scrW * (p_position.x);	
	finalPos.y = scrH * (p_position.y);
	finalTextOffset.x = scrW * (p_textOffset.x);
	finalTextOffset.y = scrH * (p_textOffset.y);

	SpriteInfo* spriteInfo = NULL;
	if( p_bgTexPath != "" )
		spriteInfo = CreateSpriteInfo( p_bgTexPath,
		fVector3(finalPos.x, finalPos.y, p_position.z),
		fVector2(p_size.x*scrW, p_size.y*scrH), NULL );


	GlyphMap* font = NULL;
	TextArea* text = NULL;
	if( p_text != "" )
	{
		text = createMenuItemTextArea(p_position, p_text, p_textOffset, p_fontSize );
		text->setText( p_text );
	}

	return new MenuItem( spriteInfo, text, font, finalPos, finalTextOffset );
}

TextArea* GOFactory::createMenuItemTextArea( fVector3 p_position,
	string p_text, fVector2 p_textOffset, fVector2 p_fontSize )
{
	float scrW = GAME_FAIL;
	float scrH = GAME_FAIL;
	if(m_io != NULL)
	{
		scrW = (float)m_io->getScreenWidth();
		scrH = (float)m_io->getScreenHeight();
	}

	unsigned int fontWidth = (unsigned int)(scrW * p_fontSize.x);
	unsigned int fontHeight = (unsigned int)(scrH * p_fontSize.y);
	float finalTextPosX = scrW * (p_position.x + p_textOffset.x);
	float finalTextPosY = scrH * (p_position.y + p_textOffset.y);

	GlyphMap* font = new GlyphMap(
			" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤",
			"../Textures/bubblemad_32x32.png", 32, 32);

	vector<GlyphAnimation*> animators;
	animators.push_back( new GlyphAnimIn() ); // Intro
	animators.push_back( new GlyphAnimSinus() ); // In menu
	animators.push_back( new GlyphAnimSinus() ); // Selected
	animators.push_back( new GlyphAnimOut() ); // Outro

	TextArea* text = new TextArea( font, p_text.size(), this, finalTextPosX,
			finalTextPosY, TextArea::CEN_CENTER,
			fVector2(fontWidth/32.0f, fontHeight/32.0f), animators);

	return text;
}

Glyph* GOFactory::CreateGlyph( const string& p_texture, float p_x,
	float p_y, fVector2 p_size, vector<GlyphAnimation*> p_animations )
{
	fVector3 pos = fVector3(p_x, p_y, 0.99f);
	SpriteInfo* spriteInfo = CreateSpriteInfo(p_texture,pos, p_size, NULL);
	// spriteInfo->visible = false;
	return new Glyph( spriteInfo );
}

GUI* GOFactory::CreateGUI(GameStats* p_gameStats)
{
	float fw = 1.0f/1920.0f;
	float fh = 1.0f/1080.0f;
	float scrW = GAME_FAIL;
	float scrH = GAME_FAIL;
	float guiHeight = 0.08f;
	if(m_io != NULL)
	{
		scrW = (float)m_io->getScreenWidth();
		scrH = (float)m_io->getScreenHeight();
	}

	float heightFraction = m_io->getScreenHeight() / 1080.0f;
	float widthFraction = m_io->getScreenWidth() / 1920.0f;
	int height = m_io->getScreenHeight();

	Rect guiRect(0, 0, m_io->getScreenWidth(),
		(int)(guiHeight) * m_io->getScreenHeight());

	vector<SpriteInfo*> lives;
	for (int i = 0; i < 3; i++)
	{
		fVector2 size = fVector2(50*widthFraction, 50*heightFraction);
		fVector3 pos = fVector3(1.1f * size.x * i + size.x*0.5f, height - 0.08f * height*0.5f, 0.9f); 

		Rect r;
		r.x		= 0;
		r.y		= 0;
		r.width = 39;
		r.height = 28;
		lives.push_back(CreateSpriteInfo("../Textures/life.png",
			pos, size, &r));
	}

	fVector2 size = fVector2(50/scrW, 50/scrH);
	size = fVector2(0,0);
	fVector3 pos = fVector3(0.3f, 1 - guiHeight*0.25f, 0.9f); 
	string texts = "ELAPSED TIME:    ";
	float fontSize = 32.0f;
	fVector2 fontSizeScaled(fontSize*fw, fontSize*fh); 
	MenuItem* elapsed = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Added by Anton

	//Par time
	pos = fVector3(0.3f, 1 - guiHeight*0.75f, 0.9f); 
	texts = "PAR TIME    :    ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	MenuItem* par = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Score
	pos = fVector3(0.6f, 1 - guiHeight*0.25f, 0.9f); 
	texts = "SCORE      :      ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	MenuItem* score = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Total Score
	pos = fVector3(0.6f, 1 - guiHeight*0.75f, 0.9f); 
	texts = "TOTAL SCORE:      ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	MenuItem* totalscore = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Victory

	VictoryStruct victoryData;

	pos = fVector3(0.5f, 0.7f, 0.9f); 
	texts = "VICTORY           ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	victoryData.victory = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.6f, 0.9f); 
	texts = "BASE SCORE:       ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	victoryData.baseScore = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.5f, 0.9f); 
	texts = "MULTIPLIER        ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	victoryData.multiplier = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.4f, 0.9f); 
	texts = "TOTAL SCORE:      ";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	victoryData.finalScore = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Pause

	PauseStruct pauseData;
	pos = fVector3(0.5f, 0.7f, 0.9f); 
	texts = "GAME PAUSED";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	pauseData.paused = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.6f, 0.9f); 
	texts = "PRESS P TO UNPAUSE";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	pauseData.pressToPlay = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//Defeat
	DefeatStruct defeatData;

	pos = fVector3(0.5f, 0.7f, 0.9f); 
	texts = "DEFEAT";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	defeatData.defeated = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.6f, 0.9f); 
	texts = "CONTINUE WILL COST HALF YOUR TOTAL SCORE";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	defeatData.cost = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(0.5f, 0.5f, 0.9f); 
	texts = "PRESS ENTER TO CONTINUE";
	fontSize = 32.0f;
	fontSizeScaled = fVector2(fontSize*fw, fontSize*fh); 
	defeatData.cont = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	//End added by Anton

	pos		= fVector3(1 - 350/scrW, 1 - guiHeight*0.5f, 0.9f);
	size	= fVector2(64*widthFraction, 64*heightFraction);
	string ytext = "Z";
	MenuItem* y = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			ytext, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3((1920-300)*widthFraction, height - 0.08f * height*0.5f, 0.9f); 
	SpriteInfo* bomb = CreateSpriteInfo("../Textures/buffguislot.png",
		pos, size, NULL);

	pos.z = pos.z + 0.01f;
	SpriteInfo* speedIcon = CreateSpriteInfo("../Textures/speedpowerup.png", pos,size,NULL);

	pos = fVector3(1 - 200/scrW, 1 - guiHeight*0.5f, 0.9f); 
	string xtext = "X";
	MenuItem* x = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			xtext, fVector2(0.0f, 0.0f), fontSizeScaled,"" );
	
	pos = fVector3((1920-150)*widthFraction, height - 0.08f * height * 0.5f, 0.9f);
	SpriteInfo* speed = CreateSpriteInfo("../Textures/itemguislot.png",
		pos, size, NULL);

	pos.z = pos.z + 0.01f;
	SpriteInfo* bombIcon = CreateSpriteInfo("../Textures/bombitem.png",pos,size,NULL);

	return new GUI(p_gameStats, lives, elapsed, score, par, totalscore, victoryData, pauseData, defeatData, x, y, speed, bomb, bombIcon, speedIcon);
}