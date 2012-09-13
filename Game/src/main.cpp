#include <stdio.h>
#include <stdlib.h>

#include <GL\glew.h>
#include <GL\glfw.h>
//
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "GLFW.lib")


int main()
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
 
	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window\n" );
		glfwTerminate();
		return -1;
	}
 
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
 
	glfwSetWindowTitle("OpenGL");

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
 
	do{
		// Draw nothing, see you in tutorial 2 !
 
		// Swap buffers
		glfwSwapBuffers();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
	glfwGetWindowParam( GLFW_OPENED ) );

	return 0;
}