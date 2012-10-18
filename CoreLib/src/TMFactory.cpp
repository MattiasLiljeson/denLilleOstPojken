#include "TMFactory.h"
#include "GOFactory.h"

TMFactory::TMFactory(IODevice* p_io, GOFactory* p_GOFactory)
{
	m_io = p_io;
	m_GOFactory = p_GOFactory;
}

TMFactory::~TMFactory()
{

}

Tilemap* TMFactory::CreateTileMap(int p_theme, int p_width, int p_height, vector<int> p_mapData)
{
	Tilemap* newTilemap;

	int m_theme = p_theme;

	if (m_theme == 1)
		m_currentTileMap = "../Textures/tilemap_garden.png";
	else if (m_theme == 2)
		m_currentTileMap = "../Textures/tilemap_winecellar.png";


	float tileSizeX = 10;
	float tileSizeY = 10;
	if(m_io)
	{
		tileSizeX = m_io->getScreenWidth() / (float)p_width;
		tileSizeY = 0.92f* m_io->getScreenHeight() / (float)p_height;
	}
	Tile** tiles = new Tile*[p_width * p_height];
	for(int row = 0; row < p_height; row++)
	{
		for(int col = 0; col < p_width; col++)
		{
			tiles[row*p_width+col] = CreateSingleTile(p_mapData[row*p_width+col],
				TilePosition(col,row),tileSizeX,tileSizeY);
		}
	}
	newTilemap = new Tilemap(p_width, p_height, tiles);
	return newTilemap;
}

Tile* TMFactory::CreateSingleTile(int p_type, TilePosition p_position,int p_tileSizeX, int p_tileSizeY)
{
	Tile* newTile;

	if(p_type > 0 && p_type <= WALLS)
		newTile = CreateWallTile(p_type, p_position,p_tileSizeX,p_tileSizeY);
	else if(p_type > WALLS && p_type <= PATHS)
		newTile = CreatePathTile(p_type, p_position,p_tileSizeX,p_tileSizeY);
	else 
		newTile = CreateBasicWalkableTile(p_position,p_tileSizeX,p_tileSizeY);

	return newTile;
}

Tile* TMFactory::CreateWallTile(int p_type, TilePosition p_position,int p_tileSizeX, int p_tileSizeY)
{
	Tile* newTile;
	int row = p_type / 30;
	int col = (p_type - (row*30)) - 1;

	Rect r;
	r.x			= col*32;
	r.y			= row*32;
	r.width		= 32;
	r.height	= 32;

	fVector3 pos	= fVector3(	p_position.x * p_tileSizeX + p_tileSizeX * 0.5f,
								p_position.y * p_tileSizeY + p_tileSizeY * 0.5f, 0.0f);
	fVector2 size	= fVector2( p_tileSizeX, p_tileSizeY );

	SpriteInfo* sprite = m_GOFactory->CreateSpriteInfo(m_currentTileMap, pos,size, &r);
	newTile = new Tile(false,p_position,p_tileSizeX,p_tileSizeY,sprite);

	return newTile;
}
Tile* TMFactory::CreatePathTile(int p_type, TilePosition p_position,int p_tileSizeX, int p_tileSizeY)
{
	Tile* newTile;
	int row = p_type / 30;
	int col = (p_type - (row*30))-1;

	Rect r;
	r.x			= col*32;
	r.y			= row*32;
	r.width		= 32;
	r.height	= 32;

	fVector3 pos	= fVector3(	p_position.x * p_tileSizeX + p_tileSizeX * 0.5f,
								p_position.y * p_tileSizeY + p_tileSizeY * 0.5f, 0.0f);
	fVector2 size	= fVector2( p_tileSizeX, p_tileSizeY );

	SpriteInfo* sprite = m_GOFactory->CreateSpriteInfo(m_currentTileMap, pos,size, &r);
	newTile = new Tile(true,p_position,p_tileSizeX,p_tileSizeY,sprite);

	return newTile;
}

Tile* TMFactory::CreateBasicWalkableTile(TilePosition p_position, int p_tileSizeX, int p_tileSizeY)
{
	Tile* newTile;
	int row = 3;
	int col = 12;

	Rect r;
	r.x			= col*32;
	r.y			= row*32;
	r.width		= 32;
	r.height	= 32;

	fVector3 pos	= fVector3(	p_position.x * p_tileSizeX + p_tileSizeX * 0.5f,
								p_position.y * p_tileSizeY + p_tileSizeY * 0.5f, 0.0f);
	fVector2 size	= fVector2( p_tileSizeX, p_tileSizeY );

	SpriteInfo* sprite = m_GOFactory->CreateSpriteInfo(m_currentTileMap, pos,size, &r);
	newTile = new Tile(true,p_position,p_tileSizeX,p_tileSizeY,sprite);

	return newTile;
}

Tile* TMFactory::CreateWallSwitch(int p_type,TilePosition p_position, int p_tileSizeX, int p_tileSizeY)
{
	Tile* newTile;
	int row = p_type / 30;
	int col = (p_type - (row*30)) - 1;

	Rect r;
	r.x			= col*32;
	r.y			= row*32;
	r.width		= 32;
	r.height	= 32;

	fVector3 pos	= fVector3(	p_position.x * p_tileSizeX + p_tileSizeX * 0.5f,
								p_position.y * p_tileSizeY + p_tileSizeY * 0.5f, 0.0f);
	fVector2 size	= fVector2( p_tileSizeX, p_tileSizeY );

	SpriteInfo* sprite = m_GOFactory->CreateSpriteInfo(m_currentTileMap, pos,size, &r);
	newTile = new Tile(false,p_position,p_tileSizeX,p_tileSizeY,sprite);

	return newTile;
}