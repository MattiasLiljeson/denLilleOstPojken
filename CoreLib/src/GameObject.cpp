#include "GameObject.h"

GameObject::GameObject()
{
	m_spriteInfo	= NULL;
	m_gameStats		= NULL;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo)
{
	m_spriteInfo	= p_spriteInfo;
	m_gameStats		= NULL;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats)
{
	m_spriteInfo	= p_spriteInfo;
	m_gameStats		= p_gameStats;
}

GameObject::~GameObject()
{
	m_spriteInfo = NULL;
	m_gameStats = NULL;
}

void GameObject::update(float p_deltaTime, InputInfo p_inputInfo)
{
}

fVector2 GameObject::getPostion() const 
{
	fVector2 position;

	position.x = m_spriteInfo->transformInfo.translation[TransformInfo::X];
	position.y = m_spriteInfo->transformInfo.translation[TransformInfo::Y];

	return position;
}

float GameObject::getRadius() const
{
   	return (m_spriteInfo->transformInfo.scale[TransformInfo::X]/4.0f);
}