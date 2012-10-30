#ifndef TRANSFORMINFO_H
#define TRANSFORMINFO_H

#include"fVector3.h"

struct TransformInfo
{
	enum Axis
	{ X, Y, Z, NUM_AXES };

	float	rotation[NUM_AXES];
	float	scale[NUM_AXES];
	float	translation[NUM_AXES];

	fVector3 getPos() 
	{	
		return fVector3(translation[X], translation[Y], translation[Z]);
	}

	void setPos( fVector3 p_pos )
	{ 
		translation[X] = p_pos.x;
		translation[Y] = p_pos.y;
		translation[Z] = p_pos.z;
	}
};

#endif