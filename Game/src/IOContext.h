#ifndef IOCONTEXT_H
#define IOCONTEXT_H

class IOContext
{
private:
	int m_screenWidth;
	int m_screenHeight;
	bool m_running;
protected:
	bool m_initialized;
public:
	IOContext(int p_screenWidth, int p_screenHeight);
	virtual ~IOContext();
	virtual int setWindowPosition(int p_x, int p_y) = 0;
	virtual int resize() = 0;
	virtual int update(float p_dt) = 0;
	virtual int draw(float p_dt) = 0;

	int getScreenWidth();
	int getScreenHeight();
	
	bool isRunning();
	void setRunning(bool p_running);
	bool isInitialized();
};

#endif