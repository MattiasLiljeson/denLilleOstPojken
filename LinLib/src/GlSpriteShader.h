#ifndef GLSPRITESHADER_H
#define GLSPRITESHADER_H

#include <CommonUtility.h>
#include <GL\glew.h>
#include <GL\glfw.h>
#include <GL\wglew.h>
#include <stdio.h>
#include <stdlib.h>

class GlSpriteShader
{
private:
	GLuint m_id;
	GLint m_position;
	GLint m_texCoord;

	GLint m_centerPositionConstant;
	GLint m_halfScaleConstant;
	GLint m_screenSizeConstant;
	
	GLuint m_sampler;
public:
	GlSpriteShader();
	char* readShader(char* p_path);

	GLuint getID();
	GLint getPostionIndex();
	GLint getTexCoordIndex();
	GLint getCenterPositionConstant();
	GLint getHalfScaleConstant();
	GLint getScreenSizeConstant();
	GLuint getTextureSampler();
};

#endif