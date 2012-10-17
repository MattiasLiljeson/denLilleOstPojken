#include "GUI.h"
#include "MenuItem.h"
#include <ToString.h>

GUI::GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_speedIcon, SpriteInfo* p_bombIcon)
{
	m_stats = p_stats;
	m_lives = p_lives;
	m_elapsedTime = p_elapsedTime;
	m_buffPowerUp = p_buff;
	m_itemPowerUp = p_item;
	m_speedIcon = p_speedIcon;
	m_bombIcon = p_bombIcon;
}
GUI::~GUI()
{
	delete m_elapsedTime;
	delete m_buffPowerUp;
	delete m_itemPowerUp;
}
void GUI::update(float p_dt)
{
	for (int i = 2; i >= m_stats->getNumLives(); i--)
		m_lives[i]->visible = false;

	string text = "ELAPSED TIME: " + toString((int)m_stats->getGameTimer()->getElapsedTime());
	m_elapsedTime->getTextArea()->setText(text);

	if (m_stats->getBuffSlot() == 0)
		m_speedIcon->visible = true;
	else
		m_speedIcon->visible = false;
	if (m_stats->getItemSlot() == 0)
		m_bombIcon->visible = true;
	else
		m_bombIcon->visible = false;
	
}