#ifndef GLSPRITESHADER_H
#define GLSPRITESHADER_H

#include "Utility.h"

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