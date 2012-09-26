#ifndef LOADMAP_H
#define LOADMAP_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class LoadMap
{
public:
	LoadMap();
	virtual ~LoadMap();
	vector<int> parseMap(string p_MapPath);
};

#endif