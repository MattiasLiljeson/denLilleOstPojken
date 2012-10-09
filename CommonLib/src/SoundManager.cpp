#include "SoundManager.h"

SoundManager::SoundManager()
{
}
SoundManager::~SoundManager()
{
	for (int i = 0; i < m_soundData.size(); i++)
	{
		delete m_soundData[i];
	}
}
void SoundManager::update(float p_dt)
{
	for (int i = 0; i < m_sounds.size(); i++)
	{
		if (m_sounds[i].GetStatus() == sf::Sound::Status::Stopped)
		{
			m_sounds[i] = m_sounds.back();
			m_sounds.pop_back();
		}
	}
}
void SoundManager::addSound(string p_path)
{
	for (int i = 0; i < m_soundData.size(); i++)
	{
		if (m_soundData[i]->path == p_path)
			return;
	}
	SoundData* s = new SoundData(p_path);
	m_soundData.push_back(s);
}
void SoundManager::playSound(string p_path)
{
	for (int i = 0; i < m_soundData.size(); i++)
	{
		if (m_soundData[i]->path == p_path)
		{
			sf::Sound s(m_soundData[i]->buffer);
			s.Play();
			m_sounds.push_back(s);		
		}
	}
}