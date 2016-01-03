#ifndef _POSTURELISTWINDOW_
#define _POSTURELISTWINDOW_

#include "MANAGER\ModelVideo.h"
#include "MANAGER\UserManager.h"
#include "posturewindow.h"
#include "globalDefs.h"

class PostureListWindow : public PostureWindow
{
	Q_OBJECT
public:
	PostureListWindow(QWidget*,QString,int,int,std::vector<ModelVideo>&);
	~PostureListWindow();

protected:
	void BuildBottomRight();

private:
	QWidget *m_qwSinglePosture;

	QLabel *m_qlImg;
	QLabel *m_qlOutline;
	QLabel *m_qlDesc;
	QLabel *m_qlNotify;
	QLabel *m_qlTitle;

	QPushButton *m_qpbOperate;
	QPushButton *m_qpbProfile;
	QPushButton *m_qpbPrev;
	QPushButton *m_qpbNext;
	QPushButton *m_qpbReturn;

	QString m_sUsername;

	QVector<ModelVideo> models;

	void InitWidgets(int i);
	void BuildSingle();

signals:
	void prev(const QString&);
	void next(const QString&);
	void display(const ModelVideo&);

private slots:
	void deletePos();
	void toDisplay();
	void toProfile();
	void toPrev();
	void toNext();
};

#endif//_POSTURELISTWINDOW_