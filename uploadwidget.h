#ifndef _UPLOADWIDGET_
#define _UPLOADWIDGET_

#include <exception>
#include "capture/CaptureManager.h"
#include <QObject>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

class UploadWidget : public QGLWidget
{
	Q_OBJECT

public:
	UploadWidget(QWidget*, CAPTURE_MODE);
	~UploadWidget();
	void Start();
	void Close();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int, int);

private:
	QTimer *m_pTimer;
	CaptureManager *m_cmCaptureManager;
	CAPTURE_MODE m_cmMode;

private slots:
	void stop();
	void cancel();

signals:
	void msg(const QString&);
	void cardMsg(bool);
};

#endif