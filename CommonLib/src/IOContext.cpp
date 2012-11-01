#include "IOContext.h"

IOContext::IOContext( int p_screenWidth, int p_screenHeight, bool p_windowed )
{
	m_running = true;

	for (int i = 0; i < InputInfo::NUM_KEYS; i++)
	{
		m_input.keys[i] = InputInfo::KEYUP;
	}

	m_screenWidth			= p_screenWidth;
	m_screenHeight			= p_screenHeight;
	m_windowed				= p_windowed;
}
IOContext::~IOContext()
{
}

bool IOContext::isRunning()
{
	return m_running;
}
void IOContext::setRunning(bool p_running)
{
	m_running = p_running;
}

const InputInfo& IOContext::getInput()
{
	return m_input;
}
