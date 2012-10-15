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
	/* Allocation: Moved to onEntry (Added by Jarl 2012-10-15)
	if (m_io)
	{
		m_factory = new GOFactory(p_io);
		p_io->clearSpriteInfos();
		m_menuItems.push_back( m_factory->createMenuItem() );
		testFont = new GlyphMap(" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤","../Textures/bubblemad_8x8.png",8,8);
		textArea = new TextArea(testFont,100,m_factory,100.0f,50.0f);
		textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234 {}");
	}
<<<<<<< HEAD
=======
	// testFont = new GlyphMap("ABCDEFGHIJKLMNOPQRSTUVWXYZ","../Textures/testglyph.png",8,8);
	testFont = new GlyphMap(" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤","../Textures/bubblemad_8x8.png",8,8);
	textArea = new TextArea(testFont,100,m_factory,100.0f,50.0f);
	textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234 {}");
	
	onEntry(); // Alternative
	*/
}

MenuState::~MenuState()
{
	// Deallocation: Moved to OnExit (Added by Jarl 2012-10-15)
	/*
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
	*/
	onExit();
}

bool MenuState::onEntry()
{
	if (!m_resourcesAllocated) // only allocate once
	{
		if (m_io)
		{
			m_factory = new GOFactory(m_io);
			m_io->clearSpriteInfos();
			if (m_factory)
			{
				m_menuItems.push_back( m_factory->createMenuItem() );
		
				// testFont = new GlyphMap("ABCDEFGHIJKLMNOPQRSTUVWXYZ","../Textures/testglyph.png",8,8);
				testFont = new GlyphMap(" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤","../Textures/bubblemad_8x8.png",8,8);
				textArea = new TextArea(testFont,100,m_factory,100.0f,50.0f);
				textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234 {}");
			}
		}
		//
		m_resourcesAllocated=true;
	}
	return true;
}

bool MenuState::onExit()
{
	if (m_resourcesAllocated) // only deallocate if allocated
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
			// Below moved from input handler
			m_io->clearSpriteInfos();
		}
		//
		m_resourcesAllocated=false;
	}
	return true;
}

void MenuState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();


		textArea->setText("HELLO WORLD, TEST FOR REALZ! # TEST:1234... DT=" + toString(p_dt) );
		textArea->update(p_dt,input); // empty implementation for now

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
		// m_io->clearSpriteInfos(); // This is now handled by onExit
		m_parent->requestStateChange(m_parent->getInGameState());
	}
	else if(p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
	{
		m_parent->terminate();
	}
}