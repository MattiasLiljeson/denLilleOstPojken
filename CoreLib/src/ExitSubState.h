#ifndef EXITSUBSTATE_H
#define EXITSUBSTATE_H

#include <string>
#include <vector>

#include "MenuSubStateInterface.h"
#include "MenuSubStateManager.h"

using namespace std;

class ExitSubState : public MenuSubStateInterface
{
public:
	vector<string> m_texts; 
	enum { EX_YES, EX_NO, EX_NUM_ITEMS };
	
	ExitSubState();
	~ExitSubState();
	void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu );
	void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu );
};

#endif // EXITSUBSTATE_H
