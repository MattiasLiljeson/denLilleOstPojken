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
		LSHIFT, RSHIFT, LCTRL, RCTRL,
		COMMA, PERIOD, DASH,

		A_KEY, B_KEY, C_KEY, D_KEY, E_KEY, F_KEY,
		G_KEY, H_KEY, I_KEY, J_KEY, K_KEY, L_KEY,
		M_KEY, N_KEY, O_KEY, P_KEY, Q_KEY, R_KEY,
		S_KEY, T_KEY, U_KEY, V_KEY, W_KEY, X_KEY,
		Y_KEY, Z_KEY,
		
		NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8, NUM_9,
		
		NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5,
		NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9,

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