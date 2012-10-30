#include "IODevice.h"
#include <algorithm>

IODevice::IODevice()
{
}

IODevice::~IODevice()
{	
	while (!m_spriteInfos.empty())
	{
		SpriteInfo* info = m_spriteInfos.back();
		delete info;
		m_spriteInfos.pop_back();
	}
}

IODevice::IODevice(IOContext* p_context)
{
	m_context = p_context;
}

InputInfo IODevice::fetchInput()
{
	return m_context->getInput();
}

void IODevice::updateSpriteInfo(int p_spriteId)
{

}

int	IODevice::draw(float p_dt)
{
	//if(m_context)
	//	m_context->draw(p_dt);

	if(m_context)
	{
		m_context->beginDraw();

		for(unsigned int spriteIndex = 0; spriteIndex < m_spriteInfos.size(); spriteIndex++)
		{
			m_context->drawSprite(m_spriteInfos[spriteIndex]);
		}

		m_context->endDraw();
	}

	return 0;
}

int IODevice::update(float p_dt)
{
	if(m_context)
		m_context->update(p_dt);
		m_soundManager.update(p_dt);

	return 0;
}

void IODevice::addSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_spriteInfos.push_back( p_spriteInfo );
	m_context->addSprite( p_spriteInfo );
}
void IODevice::removeSpriteInfo(SpriteInfo* p_spriteInfo)
{
	for (unsigned int i = 0; i < m_spriteInfos.size(); i++)
	{
		if (m_spriteInfos[i] == p_spriteInfo)
		{
			delete m_spriteInfos[i];
			m_spriteInfos[i] = m_spriteInfos.back();
			m_spriteInfos.pop_back();
		}
	}
}
void IODevice::clearSpriteInfos()
{
	for (unsigned int i = 0; i < m_spriteInfos.size(); i++)
		delete m_spriteInfos[i];
	m_spriteInfos.clear();
}

void IODevice::updateSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_context->addSprite( p_spriteInfo );
}

void IODevice::addSound(SoundInfo* p_soundInfo)
{
	m_soundManager.addSound(p_soundInfo);
}

bool IODevice::isRunning()
{
	return m_context->isRunning();
}
int	IODevice::getScreenWidth()
{
	if(m_context != NULL)
		return m_context->getScreenWidth();
	else
		return GAME_FAIL;
}
int	IODevice::getScreenHeight()
{
	if(m_context != NULL)
		return m_context->getScreenHeight();
	else
		return GAME_FAIL;
}	
void IODevice::setWindowText(string p_text)
{
	m_context->setWindowText(p_text);
}
void IODevice::toneSceneBlackAndWhite(float p_fraction)
{
	for (unsigned int i = 0; i < m_spriteInfos.size(); i++)
	{
		m_spriteInfos[i]->bwFraction = p_fraction;
		//m_spriteInfos[i]->fadeToBlackFraction = p_fraction;
	}
}
void IODevice::fadeSceneToBlack(float p_fraction)
{
	for (unsigned int i = 0; i < m_spriteInfos.size(); i++)
	{
		m_spriteInfos[i]->fadeToBlackFraction = p_fraction;
	}
}
