#include "SoundManager.h"

SoundManager::SoundManager()
{
}
SoundManager::~SoundManager()
{
	for(int i = 0; i < m_instances.size(); i++)
	{
		delete m_instances[i];
	}
	for(int i = 0; i < m_sounds.size(); i++)
	{
		delete m_sounds[i];
	}
	for (int i = 0; i < m_soundData.size(); i++)
	{
		delete m_soundData[i];
	}
}
void SoundManager::update(float p_dt)
{
	for (int i = 0; i < m_instances.size(); i++)
	{
		if(!m_instances[i]->deleted)
		{
			if (m_instances[i]->play)
			{
				m_instances[i]->play = false;
				playSound(m_instances[i]->id);
			}
		}
		else
		{
			delete m_instances[i];
			m_instances[i] = m_instances.back();
			m_instances.pop_back();
		}
	}
	for (int i = 0; i < m_sounds.size(); i++)
	{
	}
}
void SoundManager::addSound(SoundInfo* p_instance)
{
	m_instances.push_back(p_instance);
	for (int i = 0; i < m_soundData.size(); i++)
	{
		if (m_soundData[i]->path == p_instance->id)
			return;
	}
	SoundData* s = new SoundData(p_instance->id);
	m_soundData.push_back(s);
}
void SoundManager::playSound(string p_path)
{
	for (int i = 0; i < m_soundData.size(); i++)
	{
		if (m_soundData[i]->path == p_path)
		{

			sf::Sound* s = new sf::Sound(m_soundData[i]->buffer);
			m_sounds.push_back(s);	
			s->Play();	
		}
	}
}