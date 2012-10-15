#include "GUI.h"

GUI::GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives)
{
	m_stats = p_stats;
	m_lives = p_lives;
}
GUI::~GUI()
{
}
void GUI::update(float p_dt)
{
	for (int i = 2; i >= m_stats->getNumLives(); i--)
		m_lives[i]->visible = false;
}