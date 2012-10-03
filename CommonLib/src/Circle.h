#ifndef CRICLE_H
#define CIRCLE_H

#include "fVector2.h"

struct Circle
{
	fVector2 c;
	float	r;
	
	Circle(fVector2 p_c, float p_r)
	{
		c = p_c;
		r = p_r;
	}

	bool collidesWith(Circle p_other)
	{
		fVector2 diff = c - p_other.c;
		float distSqr = diff.lengthSquared();
		float totalR = r+p_other.r;
		if (distSqr < totalR * totalR)
			return true;
		return false;
	}
};

#endif