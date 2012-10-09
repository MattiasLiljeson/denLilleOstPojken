#include "GlContext.h"
#include <sstream>

GlContext* GlContext::s_instance = NULL;

GlContext::GlContext(int p_screenWidth, int p_screenHeight) : IOContext()
{
	s_instance				= this;
	m_screenWidth			= p_screenWidth;
	m_screenHeight			= p_screenHeight;
	m_totalGameTime			= 0;

	// Create texture manager and load default texture
	m_textureManager = new GlTextureManager();
	m_textureManager->getTexture("../Textures/default.png");

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

	delete m_spriteRenderer;
	delete m_textureManager;
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
	m_spriteRenderer = new GlSpriteRenderer(this);
	if (!m_spriteRenderer->isInitialized())
		return GAME_FAIL;

	m_keyMappings[InputInfo::ESC]	= GLFW_KEY_ESC;
	m_keyMappings[InputInfo::LEFT]	= GLFW_KEY_LEFT;
	m_keyMappings[InputInfo::RIGHT]	= GLFW_KEY_RIGHT;
	m_keyMappings[InputInfo::UP]	= GLFW_KEY_UP;
	m_keyMappings[InputInfo::DOWN]  = GLFW_KEY_DOWN;
	m_keyMappings[InputInfo::SPACE] = GLFW_KEY_SPACE;
	m_keyMappings[InputInfo::ENTER] = GLFW_KEY_ENTER;

	glfwSetWindowSizeCallback(setWindowSizeCB);
	posX = 400;
	posY = 300;
	m_initialized = true;

	glEnable(GL_DEPTH_TEST);

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
	if (glfwOpenWindow(getScreenWidth(), getScreenHeight(), 0, 0, 0, 0, 32, 0, 
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
		/*stringstream ss;
		ss << (int)(1.0f / p_dt);//   m_totalGameTime;
		string s = ss.str();
		s = "OpenGL - " + s + " FPS";
		glfwSetWindowTitle(s.c_str());*/
	}

	if (m_input.keys[InputInfo::LEFT] == InputInfo::KEYDOWN)
		posX -= 50 * p_dt;
	else if (m_input.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN)
		posX += 50 * p_dt;
	if (m_input.keys[InputInfo::DOWN] == InputInfo::KEYDOWN)
		posY -= 50 * p_dt;
	else if (m_input.keys[InputInfo::UP] == InputInfo::KEYDOWN)
		posY += 50 * p_dt;
	m_spriteRenderer->setPosition(posX, posY);

	if (!glfwGetWindowParam(GLFW_OPENED))
		setRunning(false);

	return 0;
}
int GlContext::draw(float p_dt)
{
	glClearColor(0, 0, 0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_spriteRenderer->draw();
	glfwSwapBuffers();
	return 0;
}

int GlContext::beginDraw()
{
	glClearColor(0, 0, 0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return GAME_OK;
}

int GlContext::drawSprite( SpriteInfo* p_spriteInfo )
{
	m_spriteRenderer->setSpriteInfo(p_spriteInfo);

	if( p_spriteInfo->textureIndex >= 0 )
	{
		GLuint texture = 0;
		m_textureManager->getTexture(p_spriteInfo->textureIndex, &texture);
		if(texture != NULL)
			m_spriteRenderer->setTexture(texture);
	}

	if(p_spriteInfo->visible)
		m_spriteRenderer->draw();
	return GAME_OK;
}

int GlContext::endDraw()
{
	glfwSwapBuffers();
	return GAME_OK;
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

int GlContext::spriteSetUnindexedTexture(SpriteInfo* p_spriteInfo)
{
	GLuint texture = 0;

	int textureIndex = p_spriteInfo->textureIndex = m_textureManager->getTexture(
		p_spriteInfo->textureFilePath, &texture);

	if(texture == 0)
		return GAME_FAIL;
	else
	{
		spriteSetTextureRect(p_spriteInfo, texture);
		return GAME_OK;
	}
}

void GlContext::setWindowText(string p_text)
{
	glfwSetWindowTitle(p_text.c_str());
}

int GlContext::spriteSetDefaultTexture(SpriteInfo* p_spriteInfo)
{
	// Texture not set -> use default.
	GLuint texture = 0;
			
	p_spriteInfo->textureIndex = m_textureManager->getTexture(
		0, &texture);	// (0 is the default texture index.)

	if(texture == 0)
		return GAME_FAIL;
	else
	{
		spriteSetTextureRect(p_spriteInfo, texture);
		return GAME_OK;
	}
}

void GlContext::spriteSetTextureRect(SpriteInfo* p_spriteInfo, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	int textureWidth, textureHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

	p_spriteInfo->textureRect.width = textureWidth;
	p_spriteInfo->textureRect.height = textureHeight;
}

int GlContext::addSprite( SpriteInfo* p_spriteInfo)
{
	int textureReadSuccess = GAME_FAIL;
	bool named = p_spriteInfo->textureFilePath != "";

	if( named )
	{
		m_textureManager->getTexture(p_spriteInfo->textureFilePath);
		spriteSetUnindexedTexture( p_spriteInfo );
		textureReadSuccess = GAME_OK;
	}
	else
	{
		spriteSetDefaultTexture( p_spriteInfo );
		textureReadSuccess = GAME_FAIL;
	}
	return textureReadSuccess;
}
