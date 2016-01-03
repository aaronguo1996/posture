#include "uploadwidget.h"

UploadWidget::UploadWidget(QWidget *parent, CAPTURE_MODE mode)
:QGLWidget(parent), m_cmMode(mode)
{
	m_cmCaptureManager = new CaptureManager(mode);
	m_pTimer = new QTimer(this);
	m_pTimer->start(30);
	//connect(m_pTimer, SIGNAL(timeout()), this, SLOT(start()));
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

UploadWidget::~UploadWidget()
{
	//delete m_cmCaptureManager;
	m_cmCaptureManager->Close();
}

void UploadWidget::initializeGL()
{
	try
	{
		if (m_cmCaptureManager->Init() != PXC_STATUS_NO_ERROR)
			throw "error in init";
		else
			m_cmCaptureManager->Start();
	}
	catch (char *str)
	{
		m_cmCaptureManager->SetFlag(1);
		emit msg(str);
		return;
	}
}

void UploadWidget::resizeGL(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(100.f, ar, 0.1f, 1000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void UploadWidget::paintGL()
{
	m_cmCaptureManager->Draw();
	if (m_cmMode == TWO_HANDS_OBJECT)
		emit cardMsg(m_cmCaptureManager->GetCardCaptured());
}

void UploadWidget::stop()
{
	m_cmCaptureManager->Stop();
}

void UploadWidget::Close()
{
	m_cmCaptureManager->Close();
}

void UploadWidget::Start()
{
	m_cmCaptureManager->Restart();
}

void UploadWidget::cancel()
{
	Close();
}