#include "AvatarJumping.h"

AvatarJumping::AvatarJumping(GameObject* p_gameObject) : GOState(p_gameObject)
{
	m_elapsedTime = 0;
	if (p_gameObject && p_gameObject->getSpriteInfo())
	{
		originalSize.x = p_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::X];
		originalSize.y = p_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::Y];
	}
}

AvatarJumping::~AvatarJumping()
{
}

int AvatarJumping::onEnter()
{
	return GAME_OK;
}

int AvatarJumping::onExit()
{
	return GAME_OK;
}

int AvatarJumping::update(float p_dt, InputInfo p_inputInfo)
{
	float jumptime = 0.5f;
	float factor;
	if (m_elapsedTime <= jumptime * 0.5f)
		factor = m_elapsedTime / (jumptime*0.5f);
	else
		factor = (jumptime - m_elapsedTime) / (jumptime*0.5f);
	if (m_gameObject && m_gameObject->getSpriteInfo())
	{
		m_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::X] = originalSize.x * (1+factor);
		m_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::Y] = originalSize.y * (1+factor);
	}
	m_elapsedTime += p_dt;
	if (m_elapsedTime > jumptime)
		m_elapsedTime = jumptime;
	return GAME_OK;
}