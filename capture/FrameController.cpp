
#include "FrameController.h"

FrameController::FrameController(float frameInterval)
{
	m_fFrameInterval = frameInterval;
	m_fLastFrameTime = 0.0f;
	m_LockState = OFF;
}

FrameController::~FrameController()
{
	//enpty
}

float FrameController::getCurrentTime()
{
	return (float)clock() / CLOCKS_PER_SEC;
}

void FrameController::setIntervalTime(float frameInterval)
{
	m_fFrameInterval = frameInterval;
}

bool FrameController::IsLocked()
{
	return m_LockState == ON;
}

void FrameController::Lock()
{
	m_LockState = ON;
}

void FrameController::Unlock()
{
	m_LockState = OFF;
}

float FrameController::Check()
{
	float curTime = getCurrentTime();
	if ((curTime - m_fLastFrameTime) > m_fFrameInterval)
	{
		Unlock();
		m_fLastFrameTime = curTime;
	}
	
	return curTime;
}