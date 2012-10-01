#ifndef IOCONTEXT_H
#define IOCONTEXT_H

#include "CommonUtility.h"
#include "InputInfo.h"
#include "SpriteInfo.h"

class IOContext
{
private:
	bool m_running;	
protected:
	InputInfo	m_input;
	bool		m_initialized;
public:
					IOContext();
	virtual			~IOContext();
	virtual bool	isInitialized() const = 0;
	virtual int		setWindowPosition(int p_x, int p_y) = 0;
	virtual int		setWindowSize(int p_width, int p_height) = 0;
	virtual int		update(float p_dt) = 0;
	virtual int		draw(float p_dt) = 0;	// Will be removed.

	virtual int		addSprite( SpriteInfo* p_spriteInfo ) = 0;

	virtual int		beginDraw() = 0;
	virtual int		drawSprite(SpriteInfo* p_spriteInfo) = 0;
	virtual int		endDraw() = 0;

	virtual int		getScreenWidth() const = 0;
	virtual int		getScreenHeight() const = 0;
	
	bool			isRunning();
	void			setRunning(bool p_running);

	const			InputInfo& getInput();
};

#endif