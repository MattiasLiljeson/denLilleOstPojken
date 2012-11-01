#include "Collectable.h"


void Collectable::InitTransformOrigin()
{
	if(m_spriteInfo != NULL)
	{
		m_origin = m_spriteInfo->transformInfo;
		m_elapsedTime=m_origin.translation[TransformInfo::X] + m_origin.translation[TransformInfo::Y];
	}
}

Collectable::Collectable(): GameObject(NULL, NULL)
{
	m_elapsedTime = 0.0f;
	m_container = NULL;
	m_consumed = false;
	InitTransformOrigin();
}
Collectable::Collectable(SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo, NULL)
{
	m_elapsedTime = 0.0f;
	m_container = NULL;
	m_consumed = false;
	InitTransformOrigin();
}
Collectable::Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats): GameObject(p_spriteInfo, p_gameStats)
{
	m_elapsedTime = 0.0f;
	m_container = NULL;
	m_consumed = false;
	InitTransformOrigin();
}
Collectable::Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats,CollectableContainer* p_container): GameObject(p_spriteInfo, p_gameStats)
{
	m_elapsedTime = 0.0f;
	m_container = p_container;
	m_consumed = false;
	InitTransformOrigin();
}

Collectable::~Collectable()
{
	if (m_container!=NULL) delete m_container;
}
bool Collectable::isConsumed()
{
	return m_consumed;
}
void Collectable::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_elapsedTime += p_deltaTime;
	if (m_container!=NULL)
	{
		if (!isConsumed())
		{ 
			// animation on map
			m_spriteInfo->transformInfo.translation[TransformInfo::Y] = m_origin.translation[TransformInfo::Y]+cos(m_elapsedTime*3.5f);
			m_spriteInfo->transformInfo.translation[TransformInfo::X] = m_origin.translation[TransformInfo::X]+sin(m_elapsedTime*3.5f);
			m_container->update(p_deltaTime);
		}
		else
			m_container->playOutro(p_deltaTime); // play pick up animation
	}
}
void Collectable::activate()
{

}