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
	m_origin = p_spriteInfo->transformInfo;
	flotyAnimTick=m_origin.translation[TransformInfo::X] + m_origin.translation[TransformInfo::Y];
}
Pill::~Pill()
{
	delete m_eatenState;
}
void Pill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	// do a floaty animation:
	flotyAnimTick+=p_deltaTime*5.0f;
	if (m_currentState != m_eatenState)
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = m_origin.translation[TransformInfo::Y]+sin(flotyAnimTick)*1.5f;
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