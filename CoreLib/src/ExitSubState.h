#ifndef EXITSUBSTATE_H
#define EXITSUBSTATE_H

#include <string>
#include <vector>

using namespace std;

class MenuSubStateManager;

class ExitSubState
{
public:
	vector<string> m_texts; 
	enum { EX_YES, EX_NO, EX_NUM_ITEMS };
	ExitSubState();
	~ExitSubState();

	void selectBtn( int p_curritemIdx, MenuSubStateManager* p_manager );
};

#endif // EXITSUBSTATE_H
