#include "GameObject.h"
#include "GOState.h"
#include "BasicIdle.h"

GameObject::GameObject()
{
	m_spriteInfo		= NULL;
	m_gameStats			= NULL;
	m_basicIdleState	= new BasicIdle(this);
	m_currentState		= m_basicIdleState;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo)
{
	m_spriteInfo		= p_spriteInfo;
	m_gameStats			= NULL;
	m_basicIdleState	= new BasicIdle(this);
	m_currentState		= m_basicIdleState;
}

GameObject::GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats)
{
	m_spriteInfo		= p_spriteInfo;
	m_gameStats			= p_gameStats;
	m_basicIdleState	= new BasicIdle(this);
	m_currentState		= m_basicIdleState;
}

GameObject::~GameObject()
{
	m_spriteInfo = NULL;
	m_gameStats = NULL;
	m_currentState = NULL;
	delete m_basicIdleState;
	m_basicIdleState = NULL;
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

//getPosition and getRadius must be updated.
//they cannot depend on spriteinformation
fVector2 GameObject::getPostion() 
{
	fVector2 position(0, 0);

	if (m_spriteInfo)
	{
		position.x = m_spriteInfo->transformInfo.translation[TransformInfo::X];
		position.y = m_spriteInfo->transformInfo.translation[TransformInfo::Y];
	}

	return position;
}

float GameObject::getRadius()
{
	if (!m_spriteInfo)
		return 0;
	return (m_spriteInfo->transformInfo.scale[TransformInfo::X]);
}
SpriteInfo* GameObject::getSpriteInfo()
{
	return m_spriteInfo;
}