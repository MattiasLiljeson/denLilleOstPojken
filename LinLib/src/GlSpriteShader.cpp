#include "GlSpriteShader.h"
#include <iostream>

GlSpriteShader::GlSpriteShader()
{
	m_initialized = false;

	//Variables holding shader data
	GLuint vertexShader, fragmentShader;
	GLint vsCompiled, fsCompiled, linked;

	//Load the shader code
	const char* vsCode = readShader("../Shaders/testGL.vert");
	const char* fsCode = readShader("../Shaders/testGL.frag");

	if (!vsCode || !fsCode)
		return;

	//Create the shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	if (!vertexShader)
		return;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragmentShader)
		return;

	//Initialize and compile the shaders with the given source
	glShaderSource(vertexShader, 1, (const GLchar**)&vsCode, NULL);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fsCode, NULL);	
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, (GLint*)&vsCompiled);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, (GLint*)&fsCompiled);

	delete[] vsCode;
	delete[] fsCode;

	if (!vsCompiled || !fsCompiled) {
        char error[255];
        glGetShaderInfoLog(vertexShader, 255, NULL, error);
        std::cout << "Vertex shader error: " << std::endl << error << std::endl;
        glGetShaderInfoLog(fragmentShader, 255, NULL, error);
        std::cout << "Fragment shader error: " << std::endl << error << std::endl;
        return;
    }

	//Create the combined shader program
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	
	glLinkProgram(m_id);
	glGetProgramiv(m_id,GL_LINK_STATUS,&linked);
	if (!linked)
		return;

	//Get a reference to the vertex index used as input to the vertex shader.
	//This is needed by the IA stage.
	m_position = glGetAttribLocation(m_id, "MCVertex");
	m_texCoord = glGetAttribLocation(m_id, "MCTexCoord");

	m_textureRectConstant		= glGetUniformLocation(m_id, "TextureRect");
	m_centerPositionConstant	= glGetUniformLocation(m_id, "CenterPosition");
	m_halfScaleConstant			= glGetUniformLocation(m_id, "HalfScale");
	m_screenSizeConstant		= glGetUniformLocation(m_id, "ScreenSize");
	m_bwFraction				= glGetUniformLocation(m_id, "bwFraction");
	m_fadeToBlackFraction		= glGetUniformLocation(m_id, "fadeToBlack");
	m_colorOverlay				= glGetUniformLocation(m_id, "colorOverlay");
	m_sampler					= glGetUniformLocation(m_id, "gSampler");

	m_initialized = true;
}
char* GlSpriteShader::readShader(char* p_path)
{
    FILE* file;
    long length;
 
	//Open file for binary reading
    file = fopen(p_path, "rb");
    if (!file)
        return NULL;

	//Determine the size of the file
    fseek(file, 0, SEEK_END);
    length = ftell(file);

	//Allocate a buffer for the data
    char* data = (char*)malloc(length+1);

	//Read the file into the data buffer
    fseek(file, 0, SEEK_SET);
    fread(data, length, 1, file);
    data[length] = 0;

	//Close the file
	fclose(file);
 
    return data;
}

GLuint GlSpriteShader::getID()
{
	return m_id;
}
GLint GlSpriteShader::getPostionIndex()
{
	return m_position;
}
GLint GlSpriteShader::getTexCoordIndex()
{
	return m_texCoord;
}
GLint GlSpriteShader::getCenterPositionConstant()
{	
	return m_centerPositionConstant;
}
GLint GlSpriteShader::getHalfScaleConstant()
{
	return m_halfScaleConstant;
}
GLint GlSpriteShader::getScreenSizeConstant()
{
	return m_screenSizeConstant;
}

GLint GlSpriteShader::getTextureRectConstant()
{
	return m_textureRectConstant;
}
GLint GlSpriteShader::getBWFraction()
{
	return m_bwFraction;
}
GLint GlSpriteShader::getFadeToBlackFraction()
{
	return m_fadeToBlackFraction;
}
GLuint GlSpriteShader::getTextureSampler()
{
	return m_sampler;
}
bool GlSpriteShader::isInitialized()
{
	return m_initialized;
}
GLint GlSpriteShader::getColorOverlay()
{
	return m_colorOverlay;
}

