
#ifndef _FRAMECONTROLLER_
#define _FRAMECONTROLLER_

#include <ctime>
#include <iostream>

enum LOCK_STATE { ON, OFF };

class FrameController
{
public:
	FrameController(float frameInterval);
	~FrameController();

	float getCurrentTime();
	void setIntervalTime(float frameInterval);
	bool IsLocked();
	void Lock();
	void Unlock();
	float Check();

private:
	float m_fLastFrameTime;
	float m_fFrameInterval;
	LOCK_STATE m_LockState;
};

#endif // _FRAMECONTROLLER_
