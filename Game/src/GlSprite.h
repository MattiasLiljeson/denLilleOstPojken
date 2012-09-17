#ifndef GLSPRITE_H
#define GLSPRITE_H

#include "GlSpriteShader.h"
#include "LodePNG.h"

class GlSprite
{
private:
	GLuint m_vertexBuffer;
	float m_positionX;
	float m_positionY;	
	GLuint m_texture;

	GlSpriteShader* m_spriteShader;

private:
	int initializeGeometry();

	//temp
	GLboolean load(string path);

public:
	GlSprite();
	virtual ~GlSprite();
	void setPosition(float p_positionX, float p_positionY);
	int draw();
};

#endif