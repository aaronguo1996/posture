
#include "CaptureManager.h"

std::mutex m_mutex;

//================================================

CaptureManager::CaptureManager(CAPTURE_MODE mode)
{
	m_pSession = NULL;
	m_pSenseManager = NULL;
	m_pHandsModel = NULL;
	m_pHandsController = NULL;
	m_pCaptureManager = NULL;
	m_pTracker = NULL;
	m_pProjection = NULL;
	m_pView = NULL;
	m_pFrameController = new FrameController(0.3);
	m_CMState = STOP;
	m_CMode = mode;
	m_iFlag = 0;
	m_isCardCaptured = false;
}

CaptureManager::~CaptureManager()
{
	ReleaseAll();
}
                                 
void CaptureManager::ReleaseAll()
{
	if (m_iFlag != 0)
		return;

	if (m_pHandsController)
		delete m_pHandsController;

	/*if (m_pView)
		delete m_pView;*/

	/*if (m_pProjection)
		m_pProjection->Release();

	if (m_pTracker)
		m_pTracker->Release();

	if (m_pCaptureManager)
		m_pCaptureManager->Release();*/

	/*if (m_pHandsModel)
		delete m_pHandsModel;*/

	if (m_pSenseManager)
	{
		m_pSenseManager->Close();
		m_pSenseManager->Release();
	}

	if (m_pSession)
		m_pSession->Release();

	if (m_pFrameController)
		delete m_pFrameController;

}

void CaptureManager::SetFlag(int f)
{
	m_iFlag = f;
}

//================================================

pxcStatus CaptureManager::Init()
{
	// Error checking Status
	pxcStatus status = PXC_STATUS_INIT_FAILED;

	// Create hand model
	m_pHandsModel = new HandsModel();
	if (!m_pHandsModel)
	{
		ReleaseAll(); 
		return status;
	}

	// Create the PXCSession
	m_pSession = PXCSession::CreateInstance();
	if (!m_pSession)
	{
		ReleaseAll();
		return status;
	}

	// Create the PXCSenseManager
	m_pSenseManager = m_pSession->CreateSenseManager();
	if (!m_pSenseManager)
	{
		ReleaseAll();
		return status;
	}

	status = m_pHandsModel->Init(m_pSenseManager);
	if (status != PXC_STATUS_NO_ERROR)
	{
		ReleaseAll();
		return status;
	}

	// Query capture manager
	m_pCaptureManager = m_pSenseManager->QueryCaptureManager();
	if (!m_pCaptureManager)
	{
		std::cout << "Fail at querying captureManager.\n";
		ReleaseAll();
		return status;
	}

	// Enable tracker
	status = m_pSenseManager->EnableTracker();
	if (status < PXC_STATUS_NO_ERROR)
	{
		std::cout << "Fail to enable tracker\n";
		ReleaseAll();
		return status;
	}

	// Query tracker
	m_pTracker = m_pSenseManager->QueryTracker();
	if (m_pTracker == NULL)
	{
		std::cout << "Fail to query tracking module\n";
		ReleaseAll();
		return status;
	}

	pxcCHAR g_calibrationFile[1024] = { 0 };
	if (wcslen(g_calibrationFile) > 0)
	{
		if (m_pTracker->SetCameraParameters(g_calibrationFile) != PXC_STATUS_NO_ERROR)
			std::cout << "Warning: failed to load camera calibration\n";
	}

	// initialize the PXCSenseManager
	status = m_pSenseManager->Init();   
	if (status != PXC_STATUS_NO_ERROR)
	{
		ReleaseAll();
		return status;
	}

	// Projection and targets
	m_pProjection = m_pSenseManager->QueryCaptureManager()->QueryDevice()->CreateProjection();
	m_vTargets.push_back(Model());
	pxcUID cosID;
	for (size_t i = 0; i < m_vTargets.size(); i++)
	{
		m_vTargets[i].cosIDs.clear();
		status = m_pTracker->Set2DTrackFromFile(m_vTargets[i].model_filename, cosID);
		m_vTargets[i].addCosID(cosID, L"2D Image");
	}

	if (status != PXC_STATUS_NO_ERROR)
	{
		std::cout << "Fail to set tracking configuration.\n";
		return status;
	}
	
	// Create Openglview which implements IView (allows creations of different views)
	m_pView = new OpenGLView();
	if (!m_pView)
	{
		ReleaseAll();
		return status;
	}

	// Bind controller with model and view and start playing
	m_pHandsController = new HandsController(m_pHandsModel, m_pView);
	if (!m_pHandsController)
	{
		ReleaseAll();
		return status;
	}

	//If we got to this stage return success
	return PXC_STATUS_NO_ERROR;
}

void CaptureManager::Start()
{
	//Change state
	m_CMState = CAPTURING;

	// Run camera frames and update information thread
	std::thread cameraThread(std::bind(&CaptureManager::GetFrame, this));
	cameraThread.detach();
}

void CaptureManager::Restart()
{
	m_CMState = CAPTURING;
	/* Run camera frames and update information thread*/
	std::thread cameraThread(std::bind(&CaptureManager::GetFrame, this));
	cameraThread.detach();
}

void CaptureManager::Draw()
{
	m_pView->renderScene();
}

void CaptureManager::Stop()
{
	//Change state
	m_CMState = STOP;
	
	//Write Buffer to file
	WriteBufferToFile(OUTFILENAME);
}

void CaptureManager::Close()
{
	ReleaseAll();
}

bool CaptureManager::WriteBufferToFile(const char* fileName)
{
	std::ofstream ofs;
	ofs.open(fileName);
	int numFrames = m_vCaptureBuffer.size();
	float beginTime;
	switch (m_CMode)
	{
	case LEFT_HAND: case RIGHT_HAND:
		std::cout << numFrames << "frames.\n";
		//Delete first 5 frames
		if (numFrames <= 5)
		{
			std::cout << "Empty Buffer.\n";
			return false;
		}
		numFrames -= 5;
		beginTime = m_vCaptureBuffer[4].m_fTime;
		for (int i = 0; i < 5; i++)
			m_vCaptureBuffer.erase(m_vCaptureBuffer.begin());

		ofs << numFrames << "\n";
		for (int i = 0; i < numFrames; i++)
		{
			ofs << i << " " << m_vCaptureBuffer[i].m_fTime - beginTime << "\n";
			for (int j = 0; j < JOINTS_NUM; j++)
			{
				ofs << j << " "
					<< m_vCaptureBuffer[i].m_Positions[j][0] << " "
					<< m_vCaptureBuffer[i].m_Positions[j][1] << " "
					<< m_vCaptureBuffer[i].m_Positions[j][2] << "\n";
			}
		}
		break;
	case TWO_HANDS:
		std::cout << numFrames / 2 << "frames.\n";
		//Delete first 5 frames
		if (numFrames <= 10)
		{
			std::cout << "Empty Buffer.\n";
			return false;
		}
		numFrames -= 10;
		beginTime = m_vCaptureBuffer[9].m_fTime;
		for (int i = 0; i < 10; i++)
			m_vCaptureBuffer.erase(m_vCaptureBuffer.begin());
		ofs << numFrames / 2 << "\n";
		for (int i = 0; i < numFrames / 2; i++)
		{
			ofs << i << " " << m_vCaptureBuffer[i * 2].m_fTime - beginTime << "\n";
			for (int j = 0; j < JOINTS_NUM; j++)
			{
				ofs << j << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][0] << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][1] << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][2] << "\n";
			}
			for (int j = 0; j < JOINTS_NUM; j++)
			{
				ofs << j + JOINTS_NUM << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][0] << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][1] << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][2] << "\n";
			}
		}
		break;
	case TWO_HANDS_OBJECT:
		std::cout << numFrames / 2 << "frames.\n";
		//Delete first 5 frames
		if (numFrames <= 10)
		{
			std::cout << "Empty Buffer.\n";
			return false;
		}
		numFrames -= 10;
		beginTime = m_vCaptureBuffer[9].m_fTime;
		for (int i = 0; i < 10; i++)
			m_vCaptureBuffer.erase(m_vCaptureBuffer.begin());
		ofs << numFrames / 2 << "\n";
		for (int i = 0; i < numFrames / 2; i++)
		{
			ofs << i << " " << m_vCaptureBuffer[i * 2].m_fTime - beginTime << "\n";
			for (int j = 0; j < JOINTS_NUM; j++)
			{
				ofs << j << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][0] << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][1] << " "
					<< m_vCaptureBuffer[i * 2].m_Positions[j][2] << "\n";
			}
			for (int j = 0; j < JOINTS_NUM; j++)
			{
				ofs << j + JOINTS_NUM << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][0] << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][1] << " "
					<< m_vCaptureBuffer[i * 2 + 1].m_Positions[j][2] << "\n";
			}
		}

		ofs << "Object info.\n";

		int numObjectFrames = m_vCaptureObjectBuffer.size();
		numObjectFrames -= 5;
		for (int i = 0; i < 5; i++)
			m_vCaptureObjectBuffer.erase(m_vCaptureObjectBuffer.begin());
		int numToDelete = 0;
		for (int i = 0; i < m_vCaptureObjectBuffer.size(); i++)
		{
			if (m_vCaptureObjectBuffer[i].m_fTime > beginTime)
				break;
			numToDelete++;
		}
		if (numObjectFrames <= numToDelete)
		{
			std::cout << "Empty object buffer.\n" << numObjectFrames;
			return false;
		}
		for (int i = 0; i < numToDelete; i++)
			m_vCaptureObjectBuffer.erase(m_vCaptureObjectBuffer.begin());
		numObjectFrames -= numToDelete;
		ofs << numObjectFrames << "\n";
		for (int i = 0; i < numObjectFrames; i++)
		{
			ofs << i << " " << m_vCaptureObjectBuffer[i].m_fTime - beginTime << "\n";
			for (int j = 0; j < 4; j++)
			{
				ofs << j << " "
					<< m_vCaptureObjectBuffer[i].m_Position[j][0] << " "
					<< m_vCaptureObjectBuffer[i].m_Position[j][1] << " "
					<< m_vCaptureObjectBuffer[i].m_Position[j][2] << "\n";
			}
		}
		break;
	}

	ofs.close();

	return true;
}

void CaptureManager::SetCaptureMode(CAPTURE_MODE mode)
{
	if (m_CMState != CAPTURING)
	    m_CMode = mode;
}

//================================================

bool CaptureManager::GetFrame()
{

	//Start working on current frame
	while (m_pSenseManager->AcquireFrame(true) == PXC_STATUS_NO_ERROR)
	{
		m_mutex.lock();
		m_pHandsModel->updateModel();

		m_pHandsController->updateView();

		Capture();

		//Finish Work on frame
		m_pSenseManager->ReleaseFrame();
		
		m_mutex.unlock();

		if (!IsCapturing())
			break;

	}

	return true;
}

Frame CaptureManager::GenerateFrame(float time, PXCHandData::IHand* handOutput)
{
	Frame frame;
	
	//Fill time of the frame
	frame.m_fTime = time;

	//Fill positions of the frame
	PXCHandData::JointData jointData;
	handOutput->QueryTrackedJoint(PXCHandData::JointType::JOINT_WRIST, jointData);
	frame.m_Positions[0][0] = jointData.positionWorld.x;
	frame.m_Positions[0][1] = jointData.positionWorld.y;
	frame.m_Positions[0][2] = jointData.positionWorld.z;

	for (int i = 2; i < MAX_NUMBER_OF_JOINTS; i++)
	{
		handOutput->QueryTrackedJoint((PXCHandData::JointType)(i), jointData);
		frame.m_Positions[i-1][0] = jointData.positionWorld.x;
		frame.m_Positions[i-1][1] = jointData.positionWorld.y;
		frame.m_Positions[i-1][2] = jointData.positionWorld.z;
	}
	return frame;
}

void CaptureManager::Capture()
{
	float cur_time = m_pFrameController->Check();
	if (!m_pFrameController->IsLocked())
	{
		switch (m_CMode)
		{
		case LEFT_HAND:
			CaptureLeftHand(cur_time);
			break;
		case RIGHT_HAND:
			CaptureRightHand(cur_time);
			break;
		case TWO_HANDS:
			CaptureBothHands(cur_time);
			break;
		case TWO_HANDS_OBJECT:
			CaputreBothHandsNObject(cur_time);
			break;
		}
		m_pFrameController->Lock();
	}
}

void CaptureManager::CaptureLeftHand(float cur_time)
{
	PXCHandData::IHand* handOutput = NULL;
	int numOfHands = m_pHandsModel->getHandData()->QueryNumberOfHands();
	int numOfLeftHands = 0;
	Frame frame;
	switch (numOfHands)
	{
	case 0:
		break;
	case 1: case 2:
		for (int index = 0; index < numOfHands; ++index)
		{
			if (m_pHandsModel->getHandData()->QueryHandData(PXCHandData::ACCESS_ORDER_BY_TIME, 0, handOutput) == PXC_STATUS_NO_ERROR)
			{
				if (handOutput->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_LEFT)
				{
					frame = GenerateFrame(cur_time, handOutput);
					numOfLeftHands++;
				}
			}
		}
		break;
	}

	if (numOfLeftHands == 0)
		qDebug() << "Real Sense cannot identify a left hand.\n";
	else if (numOfLeftHands == 1)
	{
		m_vCaptureBuffer.push_back(frame);
	}
	else if (numOfLeftHands == 2)
		qDebug() << "Real Sense has identified two left hands.\n";
}

void CaptureManager::CaptureRightHand(float cur_time)
{
	PXCHandData::IHand* handOutput = NULL;
	int numOfHands = m_pHandsModel->getHandData()->QueryNumberOfHands();
	int numOfRightHands = 0;
	Frame frame;
	switch (numOfHands)
	{
	case 0:
		break;
	case 1: case 2:
		for (int index = 0; index < numOfHands; ++index)
		{
			if (m_pHandsModel->getHandData()->QueryHandData(PXCHandData::ACCESS_ORDER_BY_TIME, index, handOutput) == PXC_STATUS_NO_ERROR)
			{
				if (handOutput->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_RIGHT)
				{
					frame = GenerateFrame(cur_time, handOutput);
					numOfRightHands++;
				}
			}
		}
		break;
	}
	if (numOfRightHands == 0)
		qDebug() << "Real Sense cannot identify a right hand.\n";
	else if (numOfRightHands == 1)
		m_vCaptureBuffer.push_back(frame);
	else if (numOfRightHands == 2)
		qDebug() << "Real Sense has identified two right hands.\n";
}

void CaptureManager::CaptureBothHands(float cur_time)
{
	PXCHandData::IHand* handOutput = NULL;
	int numOfHands = m_pHandsModel->getHandData()->QueryNumberOfHands();
	int numOfRightHands = 0, numOfLeftHands = 0;
	Frame frameLeftHand, frameRightHand;
	switch (numOfHands)
	{
	case 0: case 1:
		break;
	case 2:
		for (int index = 0; index < numOfHands; ++index)
		{
			if (m_pHandsModel->getHandData()->QueryHandData(PXCHandData::ACCESS_ORDER_BY_TIME, index, handOutput)== PXC_STATUS_NO_ERROR)
			{
				if (handOutput->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_LEFT)
				{
					frameLeftHand = GenerateFrame(cur_time, handOutput);
					numOfLeftHands++;
				}
				else if (handOutput->QueryBodySide() == PXCHandData::BodySideType::BODY_SIDE_RIGHT)
				{
					frameRightHand = GenerateFrame(cur_time, handOutput);
					numOfRightHands++;
				}
			}
		}
	}
	if (numOfHands != 2 || numOfLeftHands != 1 || numOfRightHands != 1)
		qDebug() << "Real Sense cannot identify both hands.\n";
	else
	{
		m_vCaptureBuffer.push_back(frameLeftHand);
		m_vCaptureBuffer.push_back(frameRightHand);
	}
}

void CaptureManager::CaputreBothHandsNObject(float cur_time)
{
	CaptureBothHands(cur_time);

	PXCTracker::TrackingValues  trackData;
	int updatedTrackingCount = 0;

	for (TargetIterator targetIter = m_vTargets.begin(); targetIter != m_vTargets.end(); targetIter++)
	{
		for (TrackingIterator iter = targetIter->cosIDs.begin(); iter != targetIter->cosIDs.end(); iter++)
		{
			m_pTracker->QueryTrackingValues(iter->cosID, trackData);

			if (PXCTracker::IsTracking(trackData.state))
			{
				updatedTrackingCount += (!iter->isTracking) ? 1 : 0;
				iter->isTracking = true;
				m_isCardCaptured = true;
				qDebug() << m_isCardCaptured;
				m_vCaptureObjectBuffer.push_back(GenerateFrameObject(cur_time, &trackData, m_pProjection));
			}
			else
			{
				std::cout << "Cannot identify object.\n";
				updatedTrackingCount += iter->isTracking ? 1 : 0;
				iter->isTracking = false;
				m_isCardCaptured = false;
				qDebug() << m_isCardCaptured;
			}
		}
	}

}

bool CaptureManager::IsCapturing()
{
	return m_CMState == CAPTURING;
}

// Object tracking part

PXCPointF32 CaptureManager::ProjectPoint(PXCPoint3DF32 pt, PXCPoint3DF32& translation, PXCPoint4DF32 &rotation, PXCProjection *projection)
{
	PXCPointF32 dst;		// Coordinates on the color plane
	PXCPoint3DF32 eyePt;	// Transformed coordinates in camera space
	float rotMat[3][3];
	PXCPoint4DF32 q = rotation;

	// Create the rotation matrix from the quaternion
	rotMat[0][0] = (1 - (2 * (q.y*q.y)) - (2 * (q.z*q.z))); rotMat[0][1] = ((2 * q.x*q.y) - (2 * q.w*q.z));	rotMat[0][2] = ((2 * q.x*q.z) + (2 * q.w*q.y));
	rotMat[1][0] = ((2 * q.x*q.y) + (2 * q.w*q.z));		  rotMat[1][1] = (1 - (2 * q.x*q.x) - (2 * q.z*q.z));	rotMat[1][2] = ((2 * q.y*q.z) - (2 * q.w*q.x));
	rotMat[2][0] = ((2 * q.x*q.z) - (2 * q.w*q.y));		  rotMat[2][1] = ((2 * q.y*q.z) + (2 * q.w*q.x));	rotMat[2][2] = (1 - (2 * q.x*q.x) - (2 * q.y*q.y));

	// Convert model coords into eye coords by multiplying by the translation/rotation ("model view") matrix
	eyePt.x = pt.x * rotMat[0][0] + pt.y * rotMat[0][1] + pt.z * rotMat[0][2] + translation.x;
	eyePt.y = pt.x * rotMat[1][0] + pt.y * rotMat[1][1] + pt.z * rotMat[1][2] + translation.y;
	eyePt.z = pt.x * rotMat[2][0] + pt.y * rotMat[2][1] + pt.z * rotMat[2][2] + translation.z;

	if (projection)
	{
		projection->ProjectCameraToColor(1, &eyePt, &dst);
	}
	else
	{
		dst.x = eyePt.x; //+ width / 2;
		dst.y = eyePt.y; //+ height / 2;
	}

	return dst;
}

PXCPoint3DF32 CaptureManager::ProjectPoint_3d(PXCPoint3DF32 pt, PXCPoint3DF32& translation, PXCPoint4DF32 &rotation, PXCProjection *projection)
{
	PXCPointF32 dst;		// Coordinates on the color plane
	PXCPoint3DF32 eyePt;	// Transformed coordinates in camera space
	float rotMat[3][3];
	PXCPoint4DF32 q = rotation;

	// Create the rotation matrix from the quaternion
	rotMat[0][0] = (1 - (2 * (q.y*q.y)) - (2 * (q.z*q.z))); rotMat[0][1] = ((2 * q.x*q.y) - (2 * q.w*q.z));	rotMat[0][2] = ((2 * q.x*q.z) + (2 * q.w*q.y));
	rotMat[1][0] = ((2 * q.x*q.y) + (2 * q.w*q.z));		  rotMat[1][1] = (1 - (2 * q.x*q.x) - (2 * q.z*q.z));	rotMat[1][2] = ((2 * q.y*q.z) - (2 * q.w*q.x));
	rotMat[2][0] = ((2 * q.x*q.z) - (2 * q.w*q.y));		  rotMat[2][1] = ((2 * q.y*q.z) + (2 * q.w*q.x));	rotMat[2][2] = (1 - (2 * q.x*q.x) - (2 * q.y*q.y));

	// Convert model coords into eye coords by multiplying by the translation/rotation ("model view") matrix
	eyePt.x = pt.x * rotMat[0][0] + pt.y * rotMat[0][1] + pt.z * rotMat[0][2] + translation.x;
	eyePt.y = pt.x * rotMat[1][0] + pt.y * rotMat[1][1] + pt.z * rotMat[1][2] + translation.y;
	eyePt.z = pt.x * rotMat[2][0] + pt.y * rotMat[2][1] + pt.z * rotMat[2][2] + translation.z;
	return eyePt;
}

FrameObject CaptureManager::GenerateFrameObject(float time, PXCTracker::TrackingValues *tv, PXCProjection *proj)
{
	FrameObject frameObject;
	frameObject.m_fTime = time;

	float objSize = 50;
	PXCPoint3DF32 xVec = { objSize, 0, 0 };
	PXCPoint3DF32 yVec = { 0, objSize, 0 };
	PXCPoint3DF32 zVec = { 0, 0, objSize };

	PXCPointF32 xEnd = ProjectPoint(xVec, tv->translation, tv->rotation, proj);
	PXCPoint3DF32 x_3d = ProjectPoint_3d(xVec, tv->translation, tv->rotation, proj);
	PXCPointF32 yEnd = ProjectPoint(yVec, tv->translation, tv->rotation, proj);
	PXCPoint3DF32 y_3d = ProjectPoint_3d(yVec, tv->translation, tv->rotation, proj);
	PXCPointF32 zEnd = ProjectPoint(zVec, tv->translation, tv->rotation, proj);
	PXCPoint3DF32 z_3d = ProjectPoint_3d(zVec, tv->translation, tv->rotation, proj);
	PXCPoint3DF32 O = tv->translation;
	PXCPoint3DF32 dx;
	dx.x = x_3d.x - O.x;
	dx.y = x_3d.y - O.y;
	dx.z = x_3d.z - O.z;
	PXCPoint3DF32 dy;
	dy.x = y_3d.x - O.x;
	dy.y = y_3d.y - O.y;
	dy.z = y_3d.z - O.z;
	PXCPoint3DF32 tl;
	tl.x = O.x + 1.5*dx.x + 2 * dy.x;
	tl.y = O.y + 1.5*dx.y + 2 * dy.y;
	tl.z = O.z + 1.5*dx.z + 2 * dy.z;
	PXCPoint3DF32 tr;
	tr.x = O.x - 1.5*dx.x + 2 * dy.x;
	tr.y = O.y - 1.5*dx.y + 2 * dy.y;
	tr.z = O.z - 1.5*dx.z + 2 * dy.z;
	PXCPoint3DF32 br;
	br.x = O.x - 1.5*dx.x - 2 * dy.x;
	br.y = O.y - 1.5*dx.y - 2 * dy.y;
	br.z = O.z - 1.5*dx.z - 2 * dy.z;
	PXCPoint3DF32 bl;
	bl.x = O.x + 1.5*dx.x - 2 * dy.x;
	bl.y = O.y + 1.5*dx.y - 2 * dy.y;
	bl.z = O.z + 1.5*dx.z - 2 * dy.z;

	frameObject.m_Position[BOTTOM_LEFT][0] = bl.x; frameObject.m_Position[BOTTOM_LEFT][1] = bl.y; frameObject.m_Position[BOTTOM_LEFT][2] = bl.z;
	frameObject.m_Position[BOTTOM_RIGHT][0] = br.x; frameObject.m_Position[BOTTOM_RIGHT][1] = br.y; frameObject.m_Position[BOTTOM_RIGHT][2] = br.z;
	frameObject.m_Position[TOP_LEFT][0] = tl.x; frameObject.m_Position[TOP_LEFT][1] = tl.y; frameObject.m_Position[TOP_LEFT][2] = tl.z;
	frameObject.m_Position[TOP_RIGHT][0] = tr.x; frameObject.m_Position[TOP_RIGHT][1] = tr.y; frameObject.m_Position[TOP_RIGHT][2] = tr.z;

	return frameObject;
}