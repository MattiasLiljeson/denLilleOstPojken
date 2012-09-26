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
			m_context->drawSprite(*m_spriteInfos[spriteIndex]);
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

SpriteInfo*	IODevice::addSpriteInfo(SpriteInfo p_spriteInfo)
{
	p_spriteInfo.id = m_spriteInfos.size();

	SpriteInfo* newInfo			= new SpriteInfo();
	newInfo->id					= p_spriteInfo.id;
	newInfo->textureFileName	= p_spriteInfo.textureFileName;
	newInfo->transformInfo		= p_spriteInfo.transformInfo;
	newInfo->visible			= p_spriteInfo.visible;

	m_spriteInfos.push_back(newInfo);

	return newInfo;
}

void IODevice::removeSpriteInfo(SpriteInfo p_spriteInfo)
{
	
	//if((unsigned int)p_spriteInfo.id < m_spriteInfos.size())
	//{
	//	// Give last element the id of the removed one.
	//	m_spriteInfos.back().id = p_spriteInfo.id;

	//	swap(
	//		m_spriteInfos.at(p_spriteInfo.id),
	//		m_spriteInfos.back());

	//	m_spriteInfos.pop_back();

	//}
}

bool IODevice::isRunning()
{
	return m_context->isRunning();
}
