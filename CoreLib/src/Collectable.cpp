#include "Collectable.h"

Collectable::Collectable(): GameObject(NULL, NULL)
{
	m_consumed = false;
}
Collectable::Collectable(SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo, NULL)
{
	m_consumed = false;
}
Collectable::Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats): GameObject(p_spriteInfo, p_gameStats)
{
	m_consumed = false;
}
Collectable::~Collectable()
{
}
bool Collectable::isConsumed()
{
	return m_consumed;
}
void Collectable::update(float p_deltaTime, InputInfo p_inputInfo)
{
}
void Collectable::activate()
{

}