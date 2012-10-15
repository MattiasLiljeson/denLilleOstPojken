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
	return new Avatar(spriteInfo, p_map, p_startTile, p_stats,CreateSoundInfo("../Sounds/laser_zip_mono.wav",100));
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
	
	return new Pill(spriteInfo, CreateSoundInfo("../Sounds/Plink_08.wav",100), p_tile, p_gameStats);
}

Tilemap* GOFactory::CreateTileMap(int p_width, int p_height, bool* p_initData)
{
	float tileSizeX = 10;
	float tileSizeY = 10;
	if (m_io)
	{
		tileSizeX = m_io->getScreenWidth() / (float)p_width;
		tileSizeY = m_io->getScreenHeight() / (float)p_height;
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
		s->SetVolume(p_volume);
		s->Play();

		m_io->addSound(soundInfo);

		delete s;

		return soundInfo;
	}
	return NULL;
}

MenuItem* GOFactory::createMenuItem()
{
	fVector3 pos = fVector3(400.0f, 400.0f, 0.99f);
	fVector2 size = fVector2(800.0f, 350.0f);
	SpriteInfo* spriteInfo = CreateSpriteInfo("../Textures/SplashScreen.png",
		pos, size, NULL);
	return new MenuItem(spriteInfo);
}


Glyph* GOFactory::CreateGlyph(const string& p_texture, 
							  float p_x, float p_y, fVector2 p_size)
{
	fVector3 pos = fVector3(p_x, p_y, 0.99f);
	SpriteInfo* spriteInfo = CreateSpriteInfo(p_texture,pos, p_size, NULL);
	// spriteInfo->visible = false;
	return new Glyph(spriteInfo);
}