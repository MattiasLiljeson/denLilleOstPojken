#ifndef INPUTINFO_H
#define INPUTINFO_H

struct InputInfo
{
	enum KeyState 
	{ 
		KEY_UP,
		KEY_DOWN,
		KEY_RELEASED,
		KEY_PRESSED
	};
	
	enum KeyCode 
	{ 
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE, 
		ESC,
		NUM_KEYS
	};

	KeyState keyStates[NUM_KEYS];
};

#endif