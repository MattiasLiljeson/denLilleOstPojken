#include "MapLoader.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

vector<int> MapLoader::parseMap(string p_MapPath)
{
	
	fstream file(p_MapPath);

	vector<int> mapTiles;
	int value;
	
	if(file)
	{	
		for(int i = 0; i < 100; i++)
		{
			file >> value;
			mapTiles.push_back(value);
		}
	}
	return mapTiles;
}