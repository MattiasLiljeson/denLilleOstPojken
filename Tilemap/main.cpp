#include <iostream>
#include "Tilemap.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	TileType* data = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (i == 55 || i == 22)
			data[i] = TileType::FREE_TILE;
		else
			data[i] = TileType::WALL_TILE;
	}
	Tilemap m(10, 10, data);
	delete[] data;

	m.closestFreeTile(m.getTile(TilePosition(5, 5)));
	cin.get();
	return 0;
}