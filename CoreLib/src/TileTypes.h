#ifndef TILETYPES_H
#define TILETYPES_H

enum TileTypes
{
	//All equals or below 90 will be regard as walls
	WALLS = 90,
	//All equals or below  will be regard as paths
	PATHS = 180,
	//All equals or below  will be regard as SWITCHES
	SWITCHES = 210,
	//All equals or below  will be regard as WALLSWITCHES
	WALLSWITCHES = 240,
	//The chess-boy spawn
	CBSPAWN = 271,
	//All equals or below  will be regard as EnemieSpawn
	ENEMIESPAWN = 330,
	//All equals or below  will be regard as Buffs
	BUFFS = 390,
	//All equals or below  will be regard as Item
	ITEMS = 420,
	//All equals or below  will be regard as EatAblePowerUps
	EATPOWERUP = 450,
	//All equals or below  will be regard as Traps
	TRAPS = 480
};

#endif