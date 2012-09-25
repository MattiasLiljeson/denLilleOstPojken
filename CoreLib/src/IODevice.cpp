#include "IODevice.h"
#include <algorithm>

IODevice::IODevice()
{
}

IODevice::~IODevice()
{
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
	if(m_context)
		m_context->draw(p_dt);

	return 0;
}

int IODevice::update(float p_dt)
{
	if(m_context)
		m_context->update(p_dt);

	return 0;
}

SpriteInfo*	IODevice::addSpriteInfo(SpriteInfo p_spriteInfo)
{
	p_spriteInfo.id = m_spriteInfos.size();
	m_spriteInfos.push_back(p_spriteInfo);
	
	return &m_spriteInfos.back();
}

void IODevice::removeSpriteInfo(SpriteInfo p_spriteInfo)
{
	if((unsigned int)p_spriteInfo.id < m_spriteInfos.size())
	{
		// Give last element the id of the removed one.
		m_spriteInfos.back().id = p_spriteInfo.id;

		swap(
			m_spriteInfos.at(p_spriteInfo.id),
			m_spriteInfos.back());

		m_spriteInfos.pop_back();

	}
}