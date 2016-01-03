
#ifndef _CAPTUREMANAGER_
#define _CAPTUREMANAGER_

#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <QtCore\QDebug>

#include "CaptureDataStructure.h"
#include "FrameController.h"
#include "HandsController.h"
#include "HandsModel.h"
#include "object_tracker.h"
#include "pxcsession.h"
#include "pxcsensemanager.h"
#include "pxcprojection.h"

enum CM_STATE { CAPTURING, STOP };
enum CAPTURE_MODE { LEFT_HAND, RIGHT_HAND, TWO_HANDS,TWO_HANDS_OBJECT };
static const char* OUTFILENAME = "real_Joints_Pos.txt";

class CaptureManager
{
public:

	//Constructor and Destructor
	CaptureManager(CAPTURE_MODE);
	~CaptureManager();
	//OpenGL view
	OpenGLView* m_pView;
	//Initialization
	pxcStatus Init();

	//Interfaces
	void Start();
	void Stop();
	void Close();
	void Draw();
	void Restart();
	void SetFlag(int);

	//Write buffer to a file
	bool WriteBufferToFile(const char* fileName);
	bool GetCardCaptured() const{ return m_isCardCaptured; }
	//Set capturing mode
	void SetCaptureMode(CAPTURE_MODE mode);

private:

	//Sense Manager
	PXCSession *m_pSession;
	PXCSenseManager *m_pSenseManager;

	//Hands model
	HandsModel *m_pHandsModel;

	//Hands controller
	HandsController* m_pHandsController;

	//OpenGL view
	//IView* m_pView;

	//FrameController
	FrameController *m_pFrameController;

	//Object tracking
	PXCCaptureManager * m_pCaptureManager;
	PXCTracker * m_pTracker;
	PXCProjection * m_pProjection;
	std::vector<Model> m_vTargets;

	//Buffer to store information of each frame captured by real sense
	std::vector<Frame> m_vCaptureBuffer;
	std::vector<FrameObject> m_vCaptureObjectBuffer;

	//Attributes of CaptureManager
	CM_STATE m_CMState;
	CAPTURE_MODE m_CMode;

	//Release All
	void ReleaseAll();
	int m_iFlag;
	bool m_isCardCaptured;

	//Get a Frame
	bool GetFrame();
	Frame GenerateFrame(float time, PXCHandData::IHand* handOutput);
	void Capture();

	//Different capture mode
	void CaptureLeftHand(float cur_time);
	void CaptureRightHand(float cur_time);
	void CaptureBothHands(float cur_time);
	void CaputreBothHandsNObject(float cur_time);

	//Object capturing part
	FrameObject GenerateFrameObject(float time, PXCTracker::TrackingValues *tv, PXCProjection *proj);
	PXCPointF32 ProjectPoint(PXCPoint3DF32 pt, PXCPoint3DF32& translation, PXCPoint4DF32 &rotation, PXCProjection *projection);
	PXCPoint3DF32 ProjectPoint_3d(PXCPoint3DF32 pt, PXCPoint3DF32& translation, PXCPoint4DF32 &rotation, PXCProjection *projection);

	bool IsCapturing();


};

#endif // _CAPTUREMANAGER_