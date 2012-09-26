#include "InGameState.h"
#include "StateManager.h"

InGameState::InGameState(StateManager* p_parent): State(p_parent)
{

}
void InGameState::update(float p_dt)
{
	m_parent->requestStateChange(m_parent->getMenuState());
}
void InGameState::draw(float p_dt)
{
}