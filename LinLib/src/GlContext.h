#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <IOContext.h>
#include <CommonUtility.h>
#include "GlSpriteRenderer.h"
#include "GlTextureManager.h"

class GlContext: public IOContext
{
private:
	static GlContext* s_instance;
private:
	int		m_screenWidth;
	int		m_screenHeight;
	float	m_totalGameTime;
	bool	m_initialized;
	int		m_keyMappings[InputInfo::NUM_KEYS];

	//temp
	float				posX;
	float				posY;
	GlSpriteRenderer*	m_spriteRenderer;
	GlTextureManager*	m_textureManager;

private:
	int init();
	int initGLFW();
	int initGLFWWindow();
	int initGlew();

	int spriteSetUnindexedTexture(SpriteInfo* p_spriteInfo);
	int spriteSetDefaultTexture(SpriteInfo* p_spriteInfo);

public:
							GlContext(int p_screenWidth, int p_screenHeight);
	virtual					~GlContext();
	bool					isInitialized() const;
	int						setWindowPosition(int p_x, int p_y);
	int						setWindowSize(int p_width, int p_height);
	int						update(float p_dt);

	//HACK: replace by using drawSprite(), beginDraw() and endDraw()
	int						draw(float p_dt);

	int						addSprite( SpriteInfo* p_spriteInfo);

	int						beginDraw();
	int						drawSprite(SpriteInfo* p_spriteInfo);
	int						endDraw();

	int						getScreenWidth() const;
	int						getScreenHeight() const;
	static void GLFWCALL	setWindowSizeCB(int p_width, int p_height);
};

#endif