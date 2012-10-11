#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "MenuItem.h"
#include "GOFactory.h"
#include <vector>
#include "TextArea.h"

using namespace std;

class MenuState: public State
{
private:
	IODevice* m_io;
	vector<MenuItem*> m_menuItems;
	GOFactory* m_factory;
	//
	GlyphMap* testFont;
	TextArea* textArea;
public:
	MenuState(StateManager* p_parent, IODevice* p_io);
	virtual ~MenuState();
	void update(float p_dt);
	void draw(float p_dt);
	bool onEntry();
};

#endif