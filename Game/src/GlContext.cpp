#include "GlContext.h"

void GLFWCALL My_Key_Callback(int key, int action)
{
  if (key == GLFW_KEY_ESC && action == GLFW_PRESS)
  {
	  glfwCloseWindow();
  }
}

GlContext::GlContext(int p_screenWidth, int p_screenHeight) : IOContext(p_screenWidth, p_screenHeight)
{
	m_totalGameTime = 0;
	m_initialized = false;
	if (init() != 0)
	{
		glfwTerminate();
	}
}
GlContext::~GlContext()
{
	if (m_initialized)
		glfwTerminate();

	delete m_mascot;
}
int GlContext::init()
{
	//Initialize GLFW
	if(!initGLFW())
		return 1;
	if (!initGLFWWindow())
		return 1;
	if (initGlew() != GLEW_OK)
		return 1; 

	glfwSetWindowTitle("Den lille ostpojken");
	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetKeyCallback(My_Key_Callback);
	glViewport(0, 0, getScreenWidth(), getScreenHeight()); 
	m_mascot = new GlSprite();
	m_mascotTimer = 0;
	m_initialized = true;

	return 0;
}
int GlContext::initGLFW()
{
	return glfwInit();
}
int GlContext::initGLFWWindow()
{
	//Set Window Properties
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); //Use 4x Antiliasing
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); //Major GL version
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2); //Minor GL version

	//Additional parameters for the window creation.
	//In this case it is specified that opengl with its core profile
	//is to be created. This avoids creation with support of old
	//and deprecated parts of the system.
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
	//Open the Window
	return glfwOpenWindow(getScreenWidth(), getScreenHeight(),0,0,0,0, 32,0, GLFW_WINDOW);
}
int GlContext::initGlew()
{
	return glewInit();
}
bool GlContext::isInitialized()
{
	return true;
}
int GlContext::setWindowPosition(int p_x, int p_y)
{
	glfwSetWindowPos(p_x, p_y);
	return 0;
}
int GlContext::resize()
{
	return 0;
}
int GlContext::update(float p_dt)
{
	m_totalGameTime += p_dt;

	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS || !glfwGetWindowParam(GLFW_OPENED))
		setRunning(false);


	if (m_totalGameTime - (int)m_totalGameTime < p_dt)
	{
		stringstream ss;
		ss << (int)(1.0f / p_dt);//   m_totalGameTime;
		string s = ss.str();
		s = "OpenGL - " + s + " FPS";
		glfwSetWindowTitle(s.c_str());
	}

	m_mascotTimer += p_dt * 0.1f;
	if (m_mascotTimer > 1)
		m_mascotTimer -= 1;
	m_mascot->setPosition(m_mascotTimer * getScreenWidth(), m_mascotTimer * getScreenHeight());

	return 0;
}
int GlContext::draw(float p_dt)
{
	glClearColor(0, 0, 0, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_mascot->draw();
	glfwSwapBuffers();
	return 0;
}