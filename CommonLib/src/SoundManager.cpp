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
		delete m_sounds[i];
	}
	for ( unsigned int i = 0; i < m_soundData.size(); i++ )
	{
		delete m_soundData[i];
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
				playSound(m_instances[i]);
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
		if (m_sounds[i]->GetPlayingOffset() == 0)
		{
			delete m_sounds[i];
			m_sounds[i] = m_sounds.back();
			m_sounds.pop_back();
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
			m_sounds.push_back(s);	
			s->Play();
			s->SetPlayingOffset(0.001f);
			s->SetVolume(p_info->volume);
		}
	}
}