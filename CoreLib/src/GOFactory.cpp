#include "GOFactory.h"

GOFactory::GOFactory(IODevice* p_io)
{
	m_io = p_io;
}
Avatar* GOFactory::CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats)
{
	fVector3 pos = GetCenter(p_startTile, 0.5f); 
	fVector2 size = GetScaledSize(p_startTile, 0.6f);

	Rect r;
	r.x		= 385;
	r.y		= 0;
	r.width = 385;
	r.height = 450;
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/pacman-1974_sheet.png",
		pos, size, &r);
	return new Avatar(spriteInfo, p_map, p_startTile, p_stats, CreateSoundInfo("../Sounds/laser_zip_mono.wav",100), CreateSoundInfo("../Sounds/jump.wav",100));
}
Monster* GOFactory::CreateMonster(Tile* p_tile, Tilemap* p_map)
{
	fVector3 pos = GetCenter(p_tile, 0.2f); 
	fVector2 size = GetScaledSize(p_tile, 0.9f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SeaMonster.png",
		pos, size, NULL);
	return new Monster(spriteInfo, p_tile, p_map);
}
Trap* GOFactory::CreateTrap(Tile* p_tile, Tilemap* p_map)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 0.9f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/grass.png",
		pos, size, NULL);
	return new Trap(spriteInfo, p_tile, p_map);
}
SuperPill* GOFactory::CreateSuperPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.2f); 
	fVector2 size = GetScaledSize(p_tile, 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SuperPill.png",
		pos, size, NULL);
	return new SuperPill(spriteInfo, p_tile, p_gameStats, CreateSoundInfo("../Sounds/use_power-up.wav",100));
}
SpeedPill* GOFactory::CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/drug.png",
		pos, size, NULL);
	return new SpeedPill(spriteInfo, p_tile, p_gameStats, CreateSoundInfo("../Sounds/use_power-up.wav",100));
}
Pill* GOFactory::CreatePill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 0.5f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/pill.png",
		pos, size, NULL);
	
	return new Pill(spriteInfo, CreateSoundInfo("../Sounds/new_eat_sound_2012-10-16.wav",100), p_tile, p_gameStats);
}
BombPill* GOFactory::CreateBombPill(Tile* p_tile, GameStats* p_gameStats)
{
	fVector3 pos = GetCenter(p_tile, 0.1f); 
	fVector2 size = GetScaledSize(p_tile, 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/hero.png",
		pos, size, NULL);
	return new BombPill(spriteInfo, p_tile, p_gameStats, CreateSoundInfo("../Sounds/use_power-up.wav",100));
}
Bomb* GOFactory::CreateBomb(Tile* p_tile, Tilemap* p_map)
{
	vector<pair<Tile*, SpriteInfo*>> flames;
	TilePosition dir[] = {TilePosition(1, 0), TilePosition(-1, 0), TilePosition(0, 1), TilePosition(0, -1)};
	for (int i = 0; i < 4; i++)
	{
		Tile* curr = p_map->getTile(p_tile->getTilePosition() + dir[i]);
		while (curr && curr->isFree())
		{
			fVector3 pos = GetCenter(curr, 0.6f); 
			fVector2 size = GetScaledSize(curr, 0.7f);

			Rect r;
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

	return new Bomb(flames, p_tile, p_map);
}

Tilemap* GOFactory::CreateTileMap(int p_width, int p_height, bool* p_initData)
{
	float tileSizeX = 10;
	float tileSizeY = 10;
	if (m_io)
	{
		tileSizeX = m_io->getScreenWidth() / (float)p_width;
		tileSizeY = 0.92f * m_io->getScreenHeight() / (float)p_height;
	}
	Tile** tiles = new Tile*[p_width * p_height];
	for (int row = 0; row < p_height; row++)
	{
		for (int col = 0; col < p_width; col++)
		{
			tiles[row * p_width + col] = CreateTile(p_initData[row * p_width + col],
				TilePosition(col, row), tileSizeX, tileSizeY);
		}
	}
	return new Tilemap(p_width, p_height, tiles);
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
Switch* GOFactory::CreateSwitch(Tile* p_tile, Tilemap* p_map,
	GameStats* p_gameStats, vector<TilePosition> p_targets)
{
	fVector3 pos = GetCenter(p_tile, 0.2f); 
	fVector2 size = GetScaledSize(p_tile, 0.7f);

	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/Red_button.png",
		pos, size, NULL);
	return new Switch(spriteInfo, p_tile, p_map, p_gameStats, p_targets);
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
		sf::SoundBuffer buffer;
		buffer.LoadFromFile(p_sound);
		sf::Sound* s = new sf::Sound(buffer);
		s->SetVolume((float)p_volume);
		s->Play();

		m_io->addSound(soundInfo);

		delete s;

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
		unsigned int fontWidth = (unsigned int)(scrW * p_fontSize.x);
		unsigned int fontHeight = (unsigned int)(scrH * p_fontSize.y);
		float finalTextPosX = scrW * (p_position.x + p_textOffset.x);
		float finalTextPosY = scrH * (p_position.y + p_textOffset.y);

		font = new GlyphMap(
			" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤",
			"../Textures/bubblemad_32x32.png", 32, 32);

		text = new TextArea(font, p_text.size(), this, finalTextPosX,
			finalTextPosY, TextArea::CEN_CENTER, fVector2(fontWidth/32.0f, fontHeight/32.0f));
		text->setText( p_text );
	}

	return new MenuItem( spriteInfo, text, font, finalPos, finalTextOffset );
}


Glyph* GOFactory::CreateGlyph( const string& p_texture, 
							  float p_x, float p_y, fVector2 p_size)
{
	fVector3 pos = fVector3(p_x, p_y, 0.99f);
	SpriteInfo* spriteInfo = CreateSpriteInfo(p_texture,pos, p_size, NULL);
	// spriteInfo->visible = false;
	return new Glyph(spriteInfo);
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

	Rect guiRect(0, 0, m_io->getScreenWidth(), guiHeight*m_io->getScreenHeight());

	vector<SpriteInfo*> lives;
	for (int i = 0; i < 3; i++)
	{
		fVector2 size = fVector2(50*widthFraction, 50*heightFraction);
		fVector3 pos = fVector3(1.1f * size.x * i + size.x*0.5f, height - 0.08f * height*0.5f, 0.9f); 

		Rect r;
		r.x		= 385;
		r.y		= 0;
		r.width = 385;
		r.height = 450;
		lives.push_back(CreateSpriteInfo("../Textures/pacman-1974_sheet.png",
			pos, size, &r));
	}

	fVector2 size = fVector2(50/scrW, 50/scrH);
	size = fVector2(0,0);
	fVector3 pos = fVector3(0.5f, 1 - guiHeight*0.5f, 0.9f); 
	string texts = "ELAPSED TIME:    ";
	float fontSize = 32.0f;
	fVector2 fontSizeScaled(fontSize*fw, fontSize*fh); 
	MenuItem* elapsed = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			texts, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(1- 350/scrW, 1 - guiHeight*0.5f, 0.9f); 
	string xtext = "X";
	MenuItem* x = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			xtext, fVector2(0.0f, 0.0f), fontSizeScaled,"" );
	
	pos = fVector3(1- 300/scrW, 1 - guiHeight*0.5f, 0.9f); 

	SpriteInfo* speed = CreateSpriteInfo("../Textures/drug.png",
		pos, size, NULL);


	pos = fVector3(1- 150/scrW, 1 - guiHeight*0.5f, 0.9f); 
	string ytext = "Z";
	MenuItem* y = createMenuItem( 
			pos, fVector2( 0.0f, 0.0f ),
			ytext, fVector2(0.0f, 0.0f), fontSizeScaled,"" );

	pos = fVector3(1- 100/scrW, 1 - guiHeight*0.5f, 0.9f); 

	SpriteInfo* bomb = CreateSpriteInfo("../Textures/hero.png",
		pos, size, NULL);

	return new GUI(p_gameStats, lives, elapsed, x, y, speed, bomb);
}