#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "IOContext.h"
#include "Utility.h"
#include "GlSprite.h"

void GLFWCALL My_Key_Callback(int key, int action);

class GlContext: public IOContext
{
private:
	float m_totalGameTime;

	GlSprite* m_mascot;
	float m_mascotTimer;

	bool m_initialized;

private:
	int init();
	int initGLFW();
	int initGLFWWindow();
	int initGlew();

public:
	GlContext(int p_screenWidth, int p_screenHeight);
	virtual ~GlContext();
	bool isInitialized();
	int setWindowPosition(int p_x, int p_y);
	int resize();
	int update(float p_dt);
	int draw(float p_dt);
};

#endif