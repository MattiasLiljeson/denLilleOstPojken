#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SoundInfo.h"
#include <vector>

struct ActiveSound
{
	sf::Sound* sound;
	SoundInfo* info;
};
struct ActiveSong
{
	sf::Music* song;
	SoundInfo* info;
};

class SoundManager
{
private:
	//Contains the actual sound data. The buffer.
	vector<SoundData*> m_soundData;
	vector<SongData*> m_songData;

	//Contains all sound instances. Much like sprite info
	vector<SoundInfo*> m_instances;

	//Sounds that are currently being played
	vector<ActiveSound> m_sounds;
	vector<ActiveSong> m_songs;
public:
	SoundManager();
	virtual ~SoundManager();

	void update(float p_dt);
	void addSound(SoundInfo* p_instance);
	void playSound(SoundInfo* p_info);

	void addSong(SoundInfo* p_song);

	//Stops an instance and removes it from the instance list
	void stopAndRemoveInstance(SoundInfo* p_instance);
};

#endif