#include "PillEatenState.h"

PillEatenState::PillEatenState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo, SoundInfo* p_onEatSound, GameStats* p_gameStats) : GOState(p_gameObject)
{
	m_spriteInfo = p_spriteInfo;
	m_onEatSound = p_onEatSound;
	m_gameStats = p_gameStats;
	m_elapsedTime = 0;
	if (m_spriteInfo != NULL)
	{
		m_startScale = fVector2(m_spriteInfo->transformInfo.scale[TransformInfo::X],
								m_spriteInfo->transformInfo.scale[TransformInfo::Y]);
	}
}
PillEatenState::~PillEatenState()
{
	if (m_onEatSound)
		m_onEatSound->deleted = true;
}
int PillEatenState::onEnter()
{
	//Consume the pill upon entry
	Pill* p = (Pill*)m_gameObject;
	if (m_gameStats)
		m_gameStats->pillEaten();

	if (m_onEatSound)
		m_onEatSound->play = true;

	//if (m_spriteInfo)
		//m_spriteInfo->visible = false;
	return GAME_OK;
}
int PillEatenState::onExit()
{
	//Should never return to non-eaten state
	return GAME_FAIL;
}
int PillEatenState::update(float p_dt, InputInfo p_inputInfo)
{
	m_elapsedTime += p_dt;
	if (m_elapsedTime < 0.5f)
	{
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] += p_dt * m_startScale.x*5;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_startScale.x * (2*(0.5f + m_elapsedTime));
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_startScale.y * (2*(0.5f + m_elapsedTime));
	}
	else if (m_elapsedTime < 1.0f)
	{
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] -= p_dt * m_startScale.x*5;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_startScale.x * (2*(1.0f - m_elapsedTime));
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_startScale.y * (2*(1.0f - m_elapsedTime));
	}
	else
		m_spriteInfo->visible = false;
	//m_spriteInfo->transformInfo.scale[TransformInfo::X] *= 1 + p_dt;
	//m_spriteInfo->transformInfo.scale[TransformInfo::Y] *= 1 + p_dt;
	return GAME_OK;
}