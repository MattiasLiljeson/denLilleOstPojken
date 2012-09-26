#include "Game.h"

Game::Game()
{
}
void Game::update(float p_dt)
{
	m_stateManager.update(p_dt);

	if (m_stateManager.getCurrentState() == m_stateManager.getInGameState())
		cout << "InGameState\n";
	else
		cout << "MenuState\n";
}
void Game::draw(float p_dt)
{
	m_stateManager.draw(p_dt);
}