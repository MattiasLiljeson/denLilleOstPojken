#include "MenuState.h"
#include "StateManager.h"

#include "DebugPrint.h"
#include "ToString.h"


MenuState::MenuState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_factory = new GOFactory(p_io);
	m_io = p_io;
	p_io->clearSpriteInfos();
	m_menuItems.push_back( m_factory->createMenuItem() );

	testFont = new GlyphMap("ABCDEFGHIJKLMNOPQRSTUVWXYZ","../Textures/testglyph.png",8,8);
	textArea = new TextArea(testFont,12,m_factory,300.0f,50.0f);
	textArea->setText("HELLOWORLD");
}

MenuState::~MenuState()
{
	for(unsigned int i = 0; i < m_menuItems.size(); i++)
	{
		delete m_menuItems[i];
	}

	m_menuItems.clear();

	delete testFont;
	delete textArea;


	delete m_factory;
}

bool MenuState::onEntry()
{
	return true;
}

void MenuState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		textArea->update(p_dt,input);

		if (input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED)
		{
			m_io->clearSpriteInfos();
			m_parent->requestStateChange(m_parent->getInGameState());
		}

		if( input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
		{
			m_parent->terminate();
		}
	}
}
void MenuState::draw(float p_dt)
{
}