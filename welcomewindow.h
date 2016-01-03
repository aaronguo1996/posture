#ifndef _WELCOMEWINDOW_
#define _WELCOMEWINDOW_

#include "posturewindow.h"
#include "MANAGER\ModelVideo.h"
#include <QtCore\qvector.h>
#include <QtCore\qdebug.h>

class WelcomeWindow : public PostureWindow
{
	Q_OBJECT
public:
	WelcomeWindow(QWidget*, int, ModelVideo, ModelVideo, ModelVideo, ModelVideo);
	~WelcomeWindow();
protected:
	void BuildBottomRight();

private:
	QWidget *m_qwSingle;

	QLabel *m_qlImg;
	QLabel *m_qlOutline;
	QLabel *m_qlDesc;

	QPushButton *m_qpDetail;
	QPushButton *m_qpPrev;
	QPushButton *m_qpNext;

	QVector<ModelVideo> m_qvModels;

	void BuildSingle(int i);

signals:
	void display(const ModelVideo&);
	void prev();
	void next();
	void refresh();

private slots:
	void display();
};

#endif