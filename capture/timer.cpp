#include <windows.h>
#include <string.h>
#include "timer.h"

FPSTimer::FPSTimer(void) {
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);
	fps = 0;
	fpsOut = 0;
}

int FPSTimer::Tick() {
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	fps++;

	if (now.QuadPart - last.QuadPart>freq.QuadPart) { // update every second
		last = now;
		//swprintf_s<sizeof(line)/sizeof(line[0])>(line,L"FPS=%d", fps);
		fpsOut = fps;
		fps = 0;

	}
	return fpsOut;

}