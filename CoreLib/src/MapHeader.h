#ifndef MAPHEADER_H
#define MAPHEADER_H

#include <CommonUtility.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct MapData
{
	string	name;
	string	filename;
	string	backgroundMusic;
	int		parTime;
};

class MapHeader
{
private:
	vector<MapData> m_maps;
public:
	MapHeader(string p_file);
	vector<MapData> getMaps();
};

#endif