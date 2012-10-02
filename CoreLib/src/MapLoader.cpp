#include "MapLoader.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

void MapLoader::parseMap(string p_MapPath)
{
	
	fstream file(p_MapPath.c_str());

	int value;
	int switchCount = 0;

	if(file)
	{
		file >> m_width;
		file >> m_height;
		m_map = vector<int>(m_width*m_height);
		for(int i = m_height - 1; i >= 0; i--)
		{
			for (int j = 0; j < m_width; j++)
			{
				file >> value;
				m_map[i*m_width+j] = value;
				if (value == SWITCH)
					switchCount++;
			}
		}

		int x, y;
		for (int i = 0; i < switchCount; i++)
		{
			m_switches.push_back(vector<TilePosition>());
			int affected;
			file >> affected;
			for (int j = 0; j < affected; j++)
			{
				file >> x;
				file >> y;
				m_switches.back().push_back(TilePosition(x, y));
			}
		}
	}
}

int MapLoader::getLoadedWidth()
{
	return m_width;
}

int MapLoader::getLoadedHeight()
{
	return m_height;
}
vector<int> MapLoader::getMap()
{
	return m_map;
}
vector<TilePosition> MapLoader::getSwitch(int p_index)
{
	return m_switches[p_index];
}
