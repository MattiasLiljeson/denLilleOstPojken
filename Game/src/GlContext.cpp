#include "GlContext.h"

GlContext::GlContext(int p_screenWidth, int p_screenHeight) : IOContext(p_screenWidth, p_screenHeight)
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
 
	// Open a window and create its OpenGL context
	if( !glfwOpenWindow(getScreenWidth(), getScreenHeight(),0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window\n" );
		glfwTerminate();
	}
 
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
 
	glfwSetWindowTitle("Den lille ostpojken");

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
}
GlContext::~GlContext()
{
}
int GlContext::resize()
{
	return 0;
}
int GlContext::update(float p_dt)
{
	if (!(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)))
		setRunning(false);
	return 0;
}
int GlContext::draw(float p_dt)
{
	glfwSwapBuffers();
	return 0;
}