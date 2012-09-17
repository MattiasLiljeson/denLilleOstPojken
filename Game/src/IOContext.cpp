#include "IOContext.h"

IOContext::IOContext(int p_screenWidth, int p_screenHeight)
{
	m_screenWidth = p_screenWidth;
	m_screenHeight = p_screenHeight;
	m_running = true;
}
IOContext::~IOContext()
{
}
int IOContext::getScreenWidth()
{
	return m_screenWidth;
}
int IOContext::getScreenHeight()
{
	return m_screenHeight;
}
bool IOContext::isRunning()
{
	return m_running;
}
void IOContext::setRunning(bool p_running)
{
	m_running = p_running;
}
bool IOContext::isInitialized()
{
	return m_initialized;
}