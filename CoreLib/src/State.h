#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Timer.h"
#include "IOContext.h"
#include "InputInfo.h"
#include "IODevice.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Pill.h"
#include "Monster.h"
#include "MapLoader.h"
#include "Avatar.h"
#include "SpeedPill.h"
#include "Switch.h"
#include "SuperPill.h"
#include <ctime>

class StateManager;

class State
{
protected:
	StateManager* m_parent;

	// Added by Jarl 2012-10-15
	// Bool that is used to determine whether an allocation/deallocation can be done.
	// Used to able deallocation from both onExit and Destructor. This bool should not be used
	// If the system is changed to utilise pooling.
	bool m_resourcesAllocated;

public:
	State(StateManager* p_parent);
	virtual ~State();
	virtual bool onEntry();
	virtual bool onExit();

	virtual void update(float p_dt) = 0;
	virtual void draw(float p_dt) = 0;
};

#endif