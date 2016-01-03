#ifndef _UPLOADMODEWINDOW_
#define _UPLOADMODEWINDOW_

#include "MANAGER\UserManager.h"
#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qslider.h>
#include <QtCore\qtimer.h>

class UploadModeWindow : public PostureWindow
{
	Q_OBJECT
public:
	UploadModeWindow(QWidget*);
	~UploadModeWindow();

protected:
	void BuildBottomRight();

private:
	QLabel *m_qlLeftHand;
	QLabel *m_qlRightHand;
	QLabel *m_qlCard;
	QLabel *m_qlPencil;
	QLabel *m_qlChooseModel;
	QLabel *m_qlModel;
	QLabel *m_qlFunc;

	QSlider *m_qsLeftHand;
	QSlider *m_qsRightHand;
	QSlider *m_qsCard;
	QSlider *m_qsPencil;

	QPushButton *m_qpbLeft;
	QPushButton *m_qpbRight;
	QPushButton *m_qpbBegin;
	QPushButton *m_qpbCancel;

	QTimer *m_qtTimer;

	int m_iPicNo;

	void BuildConnections();

signals:
	void toUpload(const QString&);

protected slots:
	void checkStoryValue(int);
	void checkCardValue(int);
	void record();
	void prevPic();
	void nextPic();
};

#endif//_UPLOADMODEWINDOW_