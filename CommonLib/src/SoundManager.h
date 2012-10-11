#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SoundInfo.h"
#include <vector>

class SoundManager
{
private:
	//Contains the actual sound data. The buffer.
	vector<SoundData*> m_soundData;

	//Contains all sound instances. Much like sprite info
	vector<SoundInfo*> m_instances;

	//Sounds that are currently being played
	vector<sf::Sound*> m_sounds;
public:
	SoundManager();
	virtual ~SoundManager();

	void update(float p_dt);
	void addSound(SoundInfo* p_instance);
	void playSound(string p_path);
};

#endif