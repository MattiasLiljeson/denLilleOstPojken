#include "MenuState.h"
#include "StateManager.h"

MenuState::MenuState(StateManager* p_parent): State(p_parent)
{

}
void MenuState::update(float p_dt)
{
	m_parent->requestStateChange(m_parent->getInGameState());
}
void MenuState::draw(float p_dt)
{
}