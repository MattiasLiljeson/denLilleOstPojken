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
}

void GameObject::update(float p_deltaTime, InputInfo p_inputInfo)
{
}