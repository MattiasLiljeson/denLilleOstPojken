#include "IODevice.h"
#include <algorithm>

IODevice::IODevice()
{
}

IODevice::~IODevice()
{	
	for (int i = m_spriteInfos.size() - 1; i >= 0; i--)
	{
		SpriteInfo* info = m_spriteInfos.at(i);
		m_spriteInfos.pop_back();
		delete info;
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

	return 0;
}

void IODevice::addSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_spriteInfos.push_back( p_spriteInfo );
	m_context->addSprite( p_spriteInfo );
}
void IODevice::removeSpriteInfo(SpriteInfo* p_spriteInfo)
{
	for (int i = 0; i < m_spriteInfos.size(); i++)
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
	for (int i = 0; i < m_spriteInfos.size(); i++)
		delete m_spriteInfos[i];
	m_spriteInfos.clear();
}

void IODevice::updateSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_context->addSprite( p_spriteInfo );
}

bool IODevice::isRunning()
{
	return m_context->isRunning();
}
int	IODevice::getScreenWidth()
{
	return m_context->getScreenWidth();
}
int	IODevice::getScreenHeight()
{
	return m_context->getScreenHeight();
}	
void IODevice::setWindowText(string p_text)
{
	m_context->setWindowText(p_text);
}
