#ifndef SOUNDINFO_H
#define SOUNDINFO_H

#include <SFML\Audio.hpp>
#include <string>

using namespace std;

struct SoundData
{
	sf::SoundBuffer buffer;
	string path;
	SoundData();
	SoundData(string p_path);
};

struct SoundInfo
{
	bool play;
	string id;
	bool deleted;
	float volume;
	//This struct will include more info
	//Should contain all relevant information of a 
	//sound instance.
	SoundInfo()
	{
		deleted = false;
		play	= false;
		id		= "";
		volume = 100;
	}
};

#endif