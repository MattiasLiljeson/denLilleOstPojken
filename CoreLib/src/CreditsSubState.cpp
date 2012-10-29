#include "CreditsSubState.h"
#include "MenuSubState.h"

CreditsSubState::CreditsSubState( MenuSubStateManager* p_manager )
	: MenuSubState( p_manager )
{
	m_texts.resize(CR_NUM_ITEMS);
	m_texts[CR_MAIN] = "GO BACK TO MAIN";

	m_texts.push_back("        CODER OF DESTINY: ANTON ANDERSSON ");
	m_texts.push_back("          EVIL SCIENTIST: ALEXANDER BRODEN");
	m_texts.push_back("BARBARIAN FROM THE NORTH: JOHAN CARLBERG  ");
	m_texts.push_back("      THE VIENNAN ARTIST: JARL LARSSON    ");
	m_texts.push_back("MASTER OF TIME AND SPACE: MATTIAS LILJESON");
	m_texts.push_back("                  MR CEO: ROBIN THUNSTROM ");

	// More items, Names, need more space
	m_properties.m_firstItemPos.y += 0.3f;
	//m_itemDistance *= 0.5f;
}

CreditsSubState::~CreditsSubState()
{
}

void CreditsSubState::selectBtn()
{
	if( m_currItemIdx == CR_MAIN )
	{
		m_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
}