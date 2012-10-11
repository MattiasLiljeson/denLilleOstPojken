#include "GameObject.h"
#include "GOState.h"

GameObject::GameObject()
{
	m_spriteInfo	= NULL;
	m_gameStats		= NULL;
	m_currentState	= NULL;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo)
{
	m_spriteInfo	= p_spriteInfo;
	m_gameStats		= NULL;
	m_currentState	= NULL;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats)
{
	m_spriteInfo	= p_spriteInfo;
	m_gameStats		= p_gameStats;
	m_currentState	= NULL;
}

GameObject::~GameObject()
{
	m_spriteInfo = NULL;
	m_gameStats = NULL;
	m_currentState = NULL;
}

int GameObject::switchState(GOState* p_newState, bool p_forceSwitchToSame)
{
	//Only perform switch between different states or between the same 
	//state to itself if the force flag is set.
	if (m_currentState != p_newState || p_forceSwitchToSame)
	{
		m_currentState->onExit();
		p_newState->onEnter();
		m_currentState = p_newState;
	}
	return GAME_OK;
}

void GameObject::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_currentState)
		m_currentState->update(p_deltaTime, p_inputInfo);
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