#include "MapLoader.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

vector<int> MapLoader::parseMap(string p_MapPath)
{
	
	fstream file(p_MapPath.c_str());

	vector<int> mapTiles;
	int value;
	
	if(file)
	{
		file >> m_width;
		file >> m_height;
		for(int i = 0; i < m_width * m_height; i++)
		{
			file >> value;
			mapTiles.push_back(value);
		}
	}
	return mapTiles;
}
int MapLoader::getLoadedWidth()
{
	return m_width;
}
int MapLoader::getLoadedHeight()
{
	return m_height;
}