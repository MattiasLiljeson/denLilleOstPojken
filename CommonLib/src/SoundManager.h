#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SoundInfo.h"
#include <vector>

class SoundManager
{
private:
	vector<SoundData*> m_soundData;
	vector<sf::Sound> m_sounds;
public:
	SoundManager();
	virtual ~SoundManager();

	void update(float p_dt);
	void addSound(string p_path);
	void playSound(string p_path);
};

#endif