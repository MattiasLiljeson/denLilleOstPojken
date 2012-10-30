#include "MapHeader.h"

MapHeader::MapHeader(string p_file)
{
	ifstream file;
	file.open(p_file.c_str(), ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			MapData data;
			file >> data.name;
			file >> data.filename;
			file >> data.parTime;
			file >> data.backgroundMusic;
			m_maps.push_back(data);
		}
		file.close();
	}
}
vector<MapData> MapHeader::getMaps()
{
	return m_maps;
}