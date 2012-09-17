#ifndef GLSPRITE_H
#define GLSPRITE_H

#include "Utility.h"
#include "LodePNG.h"

class GlSprite
{
private:
	GLuint m_vertexBuffer;
	GLuint m_shader;
	GLint m_vertexIndex;
	GLint m_texCoordIndex;
	GLint m_CenterPositionIndex;

	float m_positionX;
	float m_positionY;
	
	GLuint m_texture;
	GLuint m_sampler;

private:
	char* readShader(char* p_path);
	int initializeShaders();
	int initializeGeometry();

	//temp
	GLboolean load(string path);

public:
	GlSprite();
	void setPosition(float p_positionX, float p_positionY);
	int draw();
};

#endif