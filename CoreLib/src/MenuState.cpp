#include "MenuState.h"
#include "StateManager.h"

MenuState::MenuState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_io = p_io;
}
void MenuState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();
		if (input.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED)
			m_parent->requestStateChange(m_parent->getInGameState());
		if( input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
		{
			m_parent->terminate();
		}
	}
}
void MenuState::draw(float p_dt)
{
}