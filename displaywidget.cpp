#include "displaywidget.h"

float DisplayWidget::fRot = 0.0f;
float DisplayWidget::fAnimSpeed = 1.0f;
float DisplayWidget::fCurTime = 0.0f;

DisplayWidget::DisplayWidget(QString fileName, QString mode, QWidget *parent)
	:m_sFileName(fileName), m_sDisplayMode(mode), QGLWidget(parent)
{
	m_ms3d = new CMs3d(m_sDisplayMode.toStdString());
	m_pTimer = new QTimer(this);
	m_pTimer->start(10);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

void DisplayWidget::UpdateCamera()
{
	if (!viewLocked)
		g_camera.setViewByMouse();

	if (KeyPress('Z')&&KeyPress(VK_SHIFT))
		g_camera.accelerate();
	if (KeyPress('X') && KeyPress(VK_SHIFT))
		g_camera.slow();

	if (KeyPress('W') && KeyPress(VK_SHIFT))
		g_camera.moveCamera(g_camera.getSpeed());
	if (KeyPress('S') && KeyPress(VK_SHIFT))
		g_camera.moveCamera(-g_camera.getSpeed());
	if (KeyPress('A') && KeyPress(VK_SHIFT))
		g_camera.yawCamera(-g_camera.getSpeed());
	if (KeyPress('D') && KeyPress(VK_SHIFT))
		g_camera.yawCamera(g_camera.getSpeed());

	if (KeyPress('Q') && KeyPress(VK_SHIFT))
		g_camera.upHeight();
	if (KeyPress('E') && KeyPress(VK_SHIFT))
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
//- Init
//- Initialization code 
//-------------------------------------------------------------
void DisplayWidget::Init()
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
		qDebug()<< "初始化地形失败!"<< "错误";
		exit(0);
	}

	// Initialize the skybox
	if (!g_skybox.init())
	{
		qDebug()<<"初始化天空失败!"<< "错误";
		exit(0);
	}

	// Set the camera
	g_camera.setCamera(500, 35, 400, 500, 35, 399, 0, 1, 0);

	// Load ms3d file
	m_ms3d->Load(m_sFileName.toStdString().c_str());

}


void DisplayWidget::initializeGL()
{
	Init();

}

void DisplayWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)width(), (GLint)height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0, (GLfloat)width() / (GLfloat)height(), 0.1, 1200.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}

void DisplayWidget::paintGL()
{
	makeCurrent();

	//Input
	//Pressing 'b' toggles the display of bones on and off
	if (KeyPressOnce('B') && KeyPressOnce(VK_SHIFT))
		m_ms3d->SwapBoneDraw();
	//Pressing 'w' toggles the display of the meshes
	if (KeyPressOnce('M') && KeyPressOnce(VK_SHIFT))
		m_ms3d->SwapMeshDraw();
	if (KeyPressOnce('V') && KeyPressOnce(VK_SHIFT))
		viewLocked = !viewLocked;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//Pressing left and right arrows rotate the model on the y axis
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
	//Take Screenshot
	if (KeyPressOnce('P') && KeyPressOnce(VK_SHIFT))
		CImage::ScreenShot();
	UpdateCamera();

	// Render stuffs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set camera
	g_camera.setLook();

	// Render sky
	if (m_sDisplayMode.toStdString() == "2")
	{
		showBackground = true;
		showTerrain = true;
	}
	else
	{
		showBackground = false;
		showTerrain = false;
	}
	if (showBackground)
		g_skybox.render();

	// Render terrain
	if (showTerrain)
		g_terrain.render();
	
	// Render ms3d model and object
	glTranslatef(MS3D_FIX_X, MS3D_FIX_Y, MS3D_FIX_Z);
	m_ms3d->Animate(fAnimSpeed, 0, m_ms3d->TotalTime(), true, &fCurTime);
}

void DisplayWidget::print(float fX, float fY, const char * szFmt, ...)
{
	char caFinal[1024];
	va_list va;
	va_start(va, szFmt);
	vsprintf(caFinal, szFmt, va);
	va_end(va);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(fX, fY);
	glCallLists(strlen(caFinal), GL_UNSIGNED_BYTE, caFinal);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}