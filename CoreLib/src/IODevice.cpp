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

	SpriteInfo* inf			= new SpriteInfo();
	inf->id					= p_spriteInfo.id;
	inf->textureFileName	= p_spriteInfo.textureFileName;
	inf->transformInfo		= p_spriteInfo.transformInfo;
	inf->visible			= p_spriteInfo.visible;

	m_spriteInfos.push_back(inf);

	return inf;
}
SpriteInfo* IODevice::addSpriteInfo()
{
	SpriteInfo* inf = new SpriteInfo();
	inf->id = m_spriteInfos.size();
	inf->textureFileName = "";
	inf->visible = true;
	inf->transformInfo.rotation[0] = inf->transformInfo.rotation[1] = inf->transformInfo.rotation[2] = 0;
	inf->transformInfo.translation[0] = inf->transformInfo.translation[1] = inf->transformInfo.translation[2] = 0;
	inf->transformInfo.scale[0] = inf->transformInfo.scale[1] = inf->transformInfo.scale[2] = 0;
	m_spriteInfos.push_back(inf);
	return inf;
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
int	IODevice::getScreenWidth()
{
	return m_context->getScreenWidth();
}
int	IODevice::getScreenHeight()
{
	return m_context->getScreenHeight();
}
