#include "MapHeader.h"
#include "ExecutableDirectoryPath.h"

MapHeader::MapHeader(string p_file)
{
	ifstream file;
	file.open(addExecutableDirectoryPath(p_file.c_str()).c_str(), ios::in);
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
	} else {
        printf("Could not open map header for reading: %s\n", addExecutableDirectoryPath(p_file.c_str()).c_str());
    }
}
vector<MapData> MapHeader::getMaps()
{
	return m_maps;
}