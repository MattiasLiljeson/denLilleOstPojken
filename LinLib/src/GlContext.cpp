#include "GlContext.h"
#include <sstream>

GlContext* GlContext::s_instance = NULL;

GlContext::GlContext(int p_screenWidth, int p_screenHeight) : IOContext()
{
	s_instance				= this;
	m_screenWidth			= p_screenWidth;
	m_screenHeight			= p_screenHeight;
	m_totalGameTime			= 0;
	m_initialized			= false;
	if (init() != GAME_OK)
	{
		glfwTerminate();
	}
}
GlContext::~GlContext()
{
	if (m_initialized)
		glfwTerminate();

	delete m_mascot;
	s_instance = NULL;
}
int GlContext::init()
{
	//Initialize GLFW
	if(initGLFW() == GAME_FAIL)
		return GAME_FAIL;
	if (initGLFWWindow() == GAME_FAIL)
		return GAME_FAIL;
	if (initGlew() == GAME_FAIL)
		return GAME_FAIL; 

	glfwSetWindowTitle("Den lille ostpojken");
	glfwEnable( GLFW_STICKY_KEYS );
	glViewport(0, 0, getScreenWidth(), getScreenHeight()); 
	m_mascot = new GlSprite(this);
	if (!m_mascot->isInitialized())
		return GAME_FAIL;

	m_keyMappings[InputInfo::ESC]	= GLFW_KEY_ESC;
	m_keyMappings[InputInfo::LEFT]	= GLFW_KEY_LEFT;
	m_keyMappings[InputInfo::RIGHT]	= GLFW_KEY_RIGHT;
	m_keyMappings[InputInfo::UP]	= GLFW_KEY_UP;
	m_keyMappings[InputInfo::DOWN]  = GLFW_KEY_DOWN;
	m_keyMappings[InputInfo::SPACE] = GLFW_KEY_SPACE;

	glfwSetWindowSizeCallback(setWindowSizeCB);
	posX = 400;
	posY = 300;
	m_initialized = true;
	return GAME_OK;
}
int GlContext::initGLFW()
{
	if (glfwInit() != GL_TRUE)
		return GAME_FAIL;
	return GAME_OK;
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
	if (glfwOpenWindow(getScreenWidth(), getScreenHeight(),0,0,0,0, 32,0, 
		GLFW_WINDOW) != GL_TRUE)
	{
		return GAME_FAIL;
	}
	return GAME_OK;
}
int GlContext::initGlew()
{
	if (glewInit() != GLEW_OK)
		return GAME_FAIL;
	return GAME_OK;
}
bool GlContext::isInitialized() const
{
	return m_initialized;
}
int GlContext::setWindowPosition(int p_x, int p_y)
{
	glfwSetWindowPos(p_x, p_y);
	return GAME_OK;
}
int GlContext::setWindowSize(int p_width, int p_height)
{
	m_screenWidth = p_width;
	m_screenHeight = p_height;
	glfwSetWindowSize(p_width, p_height);
	glViewport(0, 0, getScreenWidth(), getScreenHeight());
	return GAME_OK;
}
int GlContext::update(float p_dt)
{
	//GLFW PRESS = If the key is currently down.

	m_totalGameTime += p_dt;
	for (int i = 0; i < InputInfo::NUM_KEYS; i++)
	{
		if (glfwGetKey(m_keyMappings[i]) == GLFW_PRESS)
		{
			if (m_input.keys[i] == InputInfo::KEYPRESSED || 
				m_input.keys[i] == InputInfo::KEYDOWN)
			{
				m_input.keys[i] = InputInfo::KEYDOWN;
			}
			else
			{
				m_input.keys[i] = InputInfo::KEYPRESSED;
			}
		}
		else
		{
			if (m_input.keys[i] == InputInfo::KEYPRESSED || 
				m_input.keys[i] == InputInfo::KEYDOWN)
			{
				m_input.keys[i] = InputInfo::KEYRELEASED;
			}
			else
			{
				m_input.keys[i] = InputInfo::KEYUP;
			}
		}
	}

	if (m_totalGameTime - (int)m_totalGameTime < p_dt)
	{
		stringstream ss;
		ss << (int)(1.0f / p_dt);//   m_totalGameTime;
		string s = ss.str();
		s = "OpenGL - " + s + " FPS";
		glfwSetWindowTitle(s.c_str());
	}

	if (m_input.keys[InputInfo::LEFT] == InputInfo::KEYDOWN)
		posX -= 50 * p_dt;
	else if (m_input.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN)
		posX += 50 * p_dt;
	if (m_input.keys[InputInfo::DOWN] == InputInfo::KEYDOWN)
		posY -= 50 * p_dt;
	else if (m_input.keys[InputInfo::UP] == InputInfo::KEYDOWN)
		posY += 50 * p_dt;
	m_mascot->setPosition(posX, posY);

	if (!glfwGetWindowParam(GLFW_OPENED))
		setRunning(false);

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

int GlContext::getScreenWidth() const
{
	return m_screenWidth;
}
int GlContext::getScreenHeight() const
{
	return m_screenHeight;
}

void GLFWCALL GlContext::setWindowSizeCB(int p_width, int p_height)
{
	if (s_instance)
		s_instance->setWindowSize(p_width, p_height);
}