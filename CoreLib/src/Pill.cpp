#include "Pill.h"
#include "PillEatenState.h"

Pill::Pill(SpriteInfo* p_spriteInfo, SoundInfo* p_soundInfo, Tile* p_tile, GameStats* p_gameStats): Collectable(p_spriteInfo, p_gameStats)
{
	if (p_gameStats)
		p_gameStats->addPill();

	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;

	m_eatenState = new PillEatenState(this, p_spriteInfo, p_soundInfo, p_gameStats);
	if(p_spriteInfo != NULL)
	{
		m_origin = p_spriteInfo->transformInfo;
		flotyAnimTick=m_origin.translation[TransformInfo::X] + m_origin.translation[TransformInfo::Y];
	}
	m_scaleTick = 0;
	m_tickUp = true;
}
Pill::~Pill()
{
	delete m_eatenState;
}
void Pill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	// do a floaty animation:
	flotyAnimTick+=p_deltaTime*5.0f;
	
	//Ticks the scale up or down depending on m_tickUp
	m_scaleTick += p_deltaTime * (m_tickUp*2-1);

	if (m_currentState != m_eatenState)
	{
		float sinFrac = sin(flotyAnimTick);
		float scaleFrac = 0.5f * sinFrac + 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = m_origin.translation[TransformInfo::Y]+sinFrac*1.5f;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_origin.scale[TransformInfo::X] * (1+scaleFrac*0.25f);
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_origin.scale[TransformInfo::Y] * (1+scaleFrac*0.25f);
		if (m_scaleTick > 1 || m_scaleTick < 0)
			m_tickUp = !m_tickUp;

	}
	// run base updates
	GameObject::update(p_deltaTime, p_inputInfo);
	m_currentState->update(p_deltaTime, p_inputInfo);
}
bool Pill::isConsumed()
{
	return m_currentState == m_eatenState;
}
void Pill::consume()
{
	switchState(m_eatenState);
}