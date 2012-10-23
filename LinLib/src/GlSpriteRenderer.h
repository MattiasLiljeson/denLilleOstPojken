#ifndef GLSPRITE_H
#define GLSPRITE_H

#include <string>
#include "GlContext.h"
#include "GlSpriteShader.h"
#include "LodePNG.h"
#include "SpriteInfo.h"
#include "GlDebug.h"

using namespace std;

class GlContext;

class GlSpriteRenderer
{
private:
	GLuint			m_vertexBuffer;
	float			m_positionX;
	float			m_positionY;	
	GLuint			m_texture;
	GlSpriteShader* m_spriteShader;
	GlContext*		m_context;
	bool			m_initialized;
	SpriteInfo*		m_spriteInfo;

private:
	int initializeGeometry();

	//temp
//	GLboolean load(string path);

public:
			GlSpriteRenderer(GlContext* p_context);
	virtual ~GlSpriteRenderer();
	void	setPosition(float p_positionX, float p_positionY);
	int		draw();
	void	setSpriteInfo( SpriteInfo* p_spriteInfo );
	void	setTexture( GLuint p_texture );

	bool	isInitialized();
};

#endif
