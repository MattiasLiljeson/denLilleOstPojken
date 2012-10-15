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
		RIGHT, LEFT, UP, DOWN, SPACE, ESC, ENTER,
		LSHIFT, RSHIFT, LCTRL, RCTRL,		// New keys
		P_KEY, W_KEY, A_KEY, S_KEY, D_KEY,	// New keys
		NUM_KEYS 
	};
	int keys[NUM_KEYS];

	InputInfo()
	{
		for(int i = 0; i < NUM_KEYS; i++)
		{
			keys[i] = KEYUP;
		}
	}
};

#endif