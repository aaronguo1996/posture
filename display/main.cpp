
//-------------------------------------------------------------
//                        INCLUDES                            -
//-------------------------------------------------------------
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include "app.h"
#include "math.h"
#include "ms3d.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Terrain.h"

const char * szTitle = "Ms3d";
const float MS3D_FIX_X = 490.0f;
const float MS3D_FIX_Y = 220.0f;
const float MS3D_FIX_Z = 300.0f;

Camera g_camera;
CMs3d g_ms3d("1");
CSkyBox g_skybox;
CTerrain g_terrain;

static bool viewLocked = false;
static bool showBackground = true;
static bool showTerrain = true;
static bool showInfo = true;

//-------------------------------------------------------------
//- Update camera
//- Update camera process
//------------------------------------------------ -------------
void UpdateCamera()
{
	if (!viewLocked)
	    g_camera.setViewByMouse();

	if (KeyPress('Z'))
		g_camera.accelerate();
	if (KeyPress('X'))
		g_camera.slow();

	if (KeyPress('W'))   
		g_camera.moveCamera(g_camera.getSpeed());          
	if (KeyPress('S')) 
		g_camera.moveCamera(-g_camera.getSpeed());        
	if (KeyPress('A')) 
		g_camera.yawCamera(-g_camera.getSpeed());          
	if (KeyPress('D')) 
		g_camera.yawCamera(g_camera.getSpeed());            

	if (KeyPress('Q'))
		g_camera.upHeight();
	if (KeyPress('E'))
		g_camera.downHeight();

	/** 根据地形高度更新摄像机 */
	Vector3 vPos = g_camera.getPosition();                  /**< 得到当前摄像机位置 */
	Vector3 vNewPos = vPos;


	/** 设置摄像机高度为 地形高度 + 20 */
	vNewPos.y = (float)g_terrain.getAveHeight(vPos.x, vPos.z) + g_camera.getHeight();

	/** 得到高度差值 */
	float temp = vNewPos.y - vPos.y;

	/** 更新摄像机方向 */
	Vector3 vView = g_camera.getView();
	vView.y += temp;

	/** 设置摄像机 */
	g_camera.setCamera(vNewPos.x, vNewPos.y, vNewPos.z,
		vView.x, vView.y, vView.z,
		0, 1, 0);
}

//-------------------------------------------------------------
//- PrintInfo
//- Print controls and information on the screen
//-------------------------------------------------------------
void printInfo(float fAnimSpeed)
{
	//Info
	APP->Print(0.5f, 0.6f, "Animation Speed: %1.1f", fAnimSpeed);
	APP->Print(0.5f, 0.5f, "Bones: %s", (g_ms3d.AreBonesEnabled() ? "Enabled" : "Disabled"));
	APP->Print(0.5f, 0.4f, "Background: %s", (showBackground ? "Enabled" : "Disabled"));
	APP->Print(0.5f, 0.3f, "Terrain: %s", (showTerrain ? "Enabled" : "Disabled"));
	APP->Print(0.5f, 0.2f, "Mesh: %s", (g_ms3d.AreMeshesEnabled() ? "Enabled" : "Disabled"));
	APP->Print(0.5f, 0.1f, "Time:%1.1f", g_ms3d.getAnimateTime());
	APP->Print(0.5f, 0.0f, "Move Speed: %1.1f", g_camera.getSpeed());
}

//-------------------------------------------------------------
//- Main
//- Main game loop
//-------------------------------------------------------------
void Main()
{
	static float fAnimSpeed = 1.0f;
	static float fCurTime = 0.0f;

	// Update info
	if (KeyPressOnce('B'))
	    g_ms3d.SwapBoneDraw();
	if (KeyPressOnce('M'))
		g_ms3d.SwapMeshDraw();

	if (KeyPressOnce(VK_LEFT))
		showBackground = !showBackground;
	if (KeyPressOnce(VK_RIGHT))
		showTerrain = !showTerrain;

	//Pressing the up and down arrows change the animation speed of the model
	if (KeyPressOnce(VK_UP))
		if (fAnimSpeed < 4.9f)
			fAnimSpeed += 0.1f;
	if (KeyPressOnce(VK_DOWN))
		if (fAnimSpeed > 0.1f)
			fAnimSpeed -= 0.1f;

	if (KeyPressOnce('I'))
		showInfo = !showInfo;

	if (KeyPressOnce('V'))
		viewLocked = !viewLocked;
	UpdateCamera();

	// Render stuffs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Draw controls and information on the screen
	if (showInfo)
	    printInfo(fAnimSpeed);

	// Set camera
	g_camera.setLook();

	// Render sky
	if (showBackground)
	    g_skybox.render();

	// Render terrain
	if (showTerrain)
	    g_terrain.render();

	// Render ms3d model and object
	glTranslatef(MS3D_FIX_X, MS3D_FIX_Y, MS3D_FIX_Z);
	g_ms3d.Animate(fAnimSpeed, 0, g_ms3d.TotalTime(), true, &fCurTime);
	
}

//-------------------------------------------------------------
//- Init
//- Initialization code 
//-------------------------------------------------------------
void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Initialize the terrain
	if (!g_terrain.init())
	{
		MessageBoxA(NULL, "初始化地形失败!", "错误", MB_OK);
		exit(0);
	}

	// Initialize the skybox
	if (!g_skybox.init())
	{
		MessageBoxA(NULL, "初始化天空失败!", "错误", MB_OK);
		exit(0);
	}

	// Set the camera
	g_camera.setCamera(500, 35, 400, 500, 35, 399, 0, 1, 0);

	// Load ms3d file
	g_ms3d.Load("demo.ms3d");

}

//-------------------------------------------------------------
//- WinMain
//- Entry point for the application
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	APP->Init(Main);
	APP->CreateWnd();
	Init();
	APP->CreateFnt("Arial", 16);
	APP->Run();
	APP->Destroy();
	return 0;
}

//-------------------------------------------------------------
//- WndProc
//- Windows Procedure for the window, put here so each app can have a custom one
//-------------------------------------------------------------
LRESULT CALLBACK CWindow::WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_CREATE:
	{
		SetWindowTextA(hWnd, szTitle);
		break;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
			//Prevent the screensaver from activating
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SIZE:
	{
		Resize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			PostQuitMessage(0);
			break;
		}
		}
		return 0;
	}
	}
	return (DefWindowProc(hWnd, uiMsg, wParam, lParam));
}