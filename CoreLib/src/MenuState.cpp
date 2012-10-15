#include "MenuState.h"
#include "StateManager.h"

#include "DebugPrint.h"
#include "ToString.h"


MenuState::MenuState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_io = p_io;
	m_factory = NULL;
	testFont = NULL;
	textArea = NULL;
	if (m_io)
	{
		m_factory = new GOFactory(p_io);
		p_io->clearSpriteInfos();
		m_menuItems.push_back( m_factory->createMenuItem() );
		testFont = new GlyphMap(" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤","../Textures/bubblemad_8x8.png",8,8);
		textArea = new TextArea(testFont,100,m_factory,100.0f,50.0f);
		textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234 {}");
	}
}

MenuState::~MenuState()
{
	if (m_io)
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


		textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234... DT=" + toString(p_dt) );
		textArea->update(p_dt,input); // empty implementation for now

		// NOTE: The way this function works right now
		// (triggers state change and sprite dealloc), 
		// it has to the last function called in update.
		handleInput(input);
	}
}
void MenuState::draw(float p_dt)
{
}

void MenuState::handleInput(InputInfo p_input)
{
	if (p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED)
	{
		m_io->clearSpriteInfos();
		m_parent->requestStateChange(m_parent->getInGameState());
	}
	else if(p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
	{
		m_parent->terminate();
	}
}