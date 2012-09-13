#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "IOContext.h"
#include "Utility.h"

class GlContext: public IOContext
{
private:
	
public:
	GlContext(int p_screenWidth, int p_screenHeight);
	virtual ~GlContext();
	int resize();
	int update(float p_dt);
	int draw(float p_dt);
};

#endif