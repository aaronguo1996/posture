
#include "CaptureManager.h"
#include "gl/glut.h"
#include <thread>

void myDisplay();
void OpenGL();

static CaptureManager* captureManager = NULL;

int main()
{
	std::thread *p = NULL;
	captureManager = new CaptureManager();
	if (captureManager->Init() != PXC_STATUS_NO_ERROR)
	{
		std::cout << "captureManager init failed.\n";
		return -1;
	}
	std::cout << "captureManager init succeeded.\n";
	std::cout << "Start capturing.\n";
	captureManager->Start();

}




