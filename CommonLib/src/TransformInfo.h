#ifndef TRANSFORMINFO_H
#define TRANSFORMINFO_H

struct TransformInfo
{
	enum Axis
	{
		X,
		Y,
		Z,
		NUM_AXES
	};

	float	rotation[NUM_AXES];
	float	scale[NUM_AXES];
	float	translation[NUM_AXES];
};

#endif