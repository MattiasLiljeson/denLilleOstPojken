#include "IOContext.h"

IOContext::IOContext()
{
	m_running = true;

	for (int i = 0; i < InputInfo::NUM_KEYS; i++)
	{
		m_input.keys[i] = InputInfo::KEYUP;
	}
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