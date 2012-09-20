#ifndef INPUTINFO_H
#define INPUTINFO_H

struct InputInfo
{
	enum KeyState
	{ 
		KEYUP, KEYDOWN, KEYRELEASED, KEYPRESSED 
	};
	enum KeyCode
	{
		RIGHT, LEFT, UP, DOWN, SPACE, ESC, NUM_KEYS 
	};
	int keys[NUM_KEYS];
};

#endif