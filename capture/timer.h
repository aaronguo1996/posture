/*************************************************************/
/*                        TIMER.H                            */
/*                                                           */
/* Purpose: Definitions and Implementation for the CTimer    */
/*          class and relatedfunctions used for timing       */
/*          purposes.                                        */
/*      Evan Pipho (evan@codershq.com)                       */
/*                                                           */
/*************************************************************/
#ifndef TIMER_H
#define TIMER_H

#pragma once

class FPSTimer {
public:

	FPSTimer(void);
	int Tick();

protected:

	LARGE_INTEGER freq, last;
	int fps;
	int fpsOut;
};

#endif //TIMER_H