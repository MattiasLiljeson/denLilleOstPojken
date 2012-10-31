#include "SoundManager.h"

SoundManager::SoundManager()
{
}
SoundManager::~SoundManager()
{
	for( unsigned int i = 0; i < m_instances.size(); i++ )
	{
		delete m_instances[i];
	}
	for( unsigned int i = 0; i < m_sounds.size(); i++ )
	{
		delete m_sounds[i].sound;
	}
	for(int i = 0; i < m_songs.size(); i++)
	{
		delete m_songs[i].song;
	}
	for ( unsigned int i = 0; i < m_soundData.size(); i++ )
	{
		delete m_soundData[i];
	}
	for (int i = 0; i < m_songData.size(); i++)
	{
		delete m_songData[i];
	}
}
void SoundManager::update(float p_dt)
{
	for ( unsigned int i = 0; i < m_instances.size(); i++ )
	{
		if(!m_instances[i]->deleted)
		{
			if (m_instances[i]->play)
			{
				m_instances[i]->play = false;
				//playSound(m_instances[i]);
			}
		}
		else
		{
			delete m_instances[i];
			m_instances[i] = m_instances.back();
			m_instances.pop_back();
		}
	}
	for ( unsigned int i = 0; i < m_sounds.size(); i++ )
	{
		m_sounds[i].sound->SetVolume(m_sounds[i].info->volume);
		if (m_sounds[i].sound->GetPlayingOffset() == 0)
		{
			delete m_sounds[i].sound;
			m_sounds[i] = m_sounds.back();
			m_sounds.pop_back();
		}
	}
	
	for (int i = 0; i < m_songs.size(); i++)
	{
		if (m_songs[i].info->deleted)
		{
			stopAndRemoveInstance(m_songs[i].info);
			delete m_songs[i].song;
			m_songs[i] = m_songs.back();
			m_songs.pop_back();
			i--;
		}
		else
		{
			m_songs[i].song->SetVolume(m_songs[i].info->volume);
		}
	}
}
void SoundManager::addSound(SoundInfo* p_instance)
{
	m_instances.push_back(p_instance);
	for ( unsigned int i = 0; i < m_soundData.size(); i++ )
	{
		if (m_soundData[i]->path == p_instance->id)
			return;
	}
	SoundData* s = new SoundData(p_instance->id);
	m_soundData.push_back(s);
}
void SoundManager::playSound(SoundInfo* p_info)
{
	for ( unsigned int i = 0; i < m_soundData.size(); i++ )
	{
		if (m_soundData[i]->path == p_info->id)
		{
			sf::Sound* s = new sf::Sound(m_soundData[i]->buffer);

			ActiveSound activeSound;
			activeSound.sound = s;
			activeSound.info = p_info;
			m_sounds.push_back(activeSound);	
			s->Play();
			s->SetPlayingOffset(0.001f);
			s->SetVolume(p_info->volume);
			return;
		}
	}

	for (int i = 0; i < m_songData.size(); i++)
	{
		if (m_songData[i]->path == p_info->id)
		{
			sf::Music* s = new sf::Music();
			s->OpenFromFile(p_info->id);
			ActiveSong activeSong;
			activeSong.song = s;
			activeSong.info = p_info;
			m_songs.push_back(activeSong);	
			s->Play();
			s->SetVolume(p_info->volume);
			s->SetLoop(true);
		}
	}
}

void SoundManager::addSong(SoundInfo* p_song)
{
	m_instances.push_back(p_song);
	for (int i = 0; i < m_songData.size(); i++)
	{
		if (m_songData[i]->path == p_song->id)
			return;
	}
	SongData* s = new SongData(p_song->id);
	m_songData.push_back(s);
}
void SoundManager::stopAndRemoveInstance(SoundInfo* p_instance)
{
	//Remove the playing sound
	for (int i = 0; i < m_sounds.size(); i++)
	{
		if (m_sounds[i].info == p_instance)
		{
			delete m_sounds[i].sound;
			m_sounds[i] = m_sounds.back();
			m_sounds.pop_back();
			i--;
		}
	}

	//Remove the instance
	for (int i = 0; i < m_instances.size(); i++)
	{
		if(m_instances[i] == p_instance)
		{
			delete m_instances[i];
			m_instances[i] = m_instances.back();
			m_instances.pop_back();
			i--;
		}
	}
}