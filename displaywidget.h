#ifndef _DISPLAYWIDGET_
#define _DISPLAYWIDGET_

#include <QtOpenGL\qgl.h>
#include <QtGui\qopenglfunctions.h>
#include <QtCore\qtimer.h>
#include <QtCore\qdebug.h>
#include "display\ms3d.h"
#include <gl/gl.h>
#include "display\math.h"
#include "display\ms3d.h"
#include "display\CameraDisplay.h"
#include "display\SkyBox.h"
#include "display\Terrain.h"
#include "globalDefs.h"

static bool viewLocked = true;
static bool showBackground = false;
static bool showTerrain = false;
static bool showInfo = true;

#define PI 3.1415

class DisplayWidget : public QGLWidget
{
public:
	DisplayWidget(QString, QString, QWidget *parent);

protected:
	void initializeGL();
	void resizeGL(int, int);
	void paintGL();

private:
	CMs3d *m_ms3d;
	CameraDisplay g_camera;
	CSkyBox g_skybox;
	CTerrain g_terrain;
	QTimer *m_pTimer;
	QString m_sFileName;
	QString m_sDisplayMode;
	static float fRot;
	static float fAnimSpeed;
	static float fCurTime;
	const char * szTitle = "Ms3d";
	const float MS3D_FIX_X = 490.0f;
	const float MS3D_FIX_Y = 220.0f;
	const float MS3D_FIX_Z = 300.0f;
	void print(float, float, const char*, ...);
	void Init();
	void UpdateCamera();
};

//-------------------------------------------------------------
//- KeyPressOnce
//- Check to see if a key has been pressed, only trigger once 
//- per press (no press and hold) 
//-------------------------------------------------------------
inline bool KeyPressOnce(int iKey)
{
	if (GetAsyncKeyState(iKey) == -32767)
		return true;
	return false;
}

//-------------------------------------------------------------
//- KeyPress
//- Check to see if a key is 
//-------------------------------------------------------------
inline bool KeyPress(int iKey)
{
	if (GetAsyncKeyState(iKey) == -32767 || GetAsyncKeyState(iKey) == -32768)
		return true;
	return false;
}

#endif