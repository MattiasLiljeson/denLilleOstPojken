#include "GameObject.h"

GameObject::GameObject()
{
	m_spriteInfo = NULL;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo)
{
	m_spriteInfo = p_spriteInfo;
}

GameObject::~GameObject()
{
}

void GameObject::update(float p_deltaTime, InputInfo p_inputInfo)
{
}