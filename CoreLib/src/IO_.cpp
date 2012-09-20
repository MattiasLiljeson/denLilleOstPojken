#include "IO_.h"
#include <algorithm>

IO::IO()
{
}

IO::~IO()
{
	delete m_context;
}

IO::IO(IIOContext* p_context)
{
	m_context = p_context;
}

InputInfo IO::fetchInput()
{
	return m_context->fetchInput();
}

void IO::updateSpriteInfo(int p_spriteId)
{

}

int	IO::draw()
{
	m_context->draw();

	return 0;
}

SpriteInfo*	IO::addSpriteInfo(SpriteInfo p_spriteInfo)
{
	p_spriteInfo.id = m_spriteInfos.size();
	m_spriteInfos.push_back(p_spriteInfo);
	
	return &m_spriteInfos.back();
}

void IO::removeSpriteInfo(SpriteInfo p_spriteInfo)
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