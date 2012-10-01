#ifndef MAPLOADER_H
#define MAPLOADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class MapLoader
{
public:
	MapLoader();
	virtual ~MapLoader();
	
	vector<int> parseMap(string p);
};

#endif