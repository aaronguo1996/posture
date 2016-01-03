#ifndef _POSTUREWINDOW_
#define _POSTUREWINDOW_

#include <qobject.h>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlayout.h>
#include <QtGui\qpixmap.h>
#include <QtGui\qicon.h>
#include <QtCore\qdebug.h>

#include "globalDefs.h"

#define OFFSET 100
#define SPACE 30

class PostureWindow : public QWidget
{
	Q_OBJECT
public:
	PostureWindow(QWidget*);
	~PostureWindow();
	void CloseFuncs();

protected:
	QWidget *m_qwBottomRight;
	QWidget *m_qwRight;
	QPushButton *m_qpRefresh;
	void BuildBottomRight();
	void BuildRight();
	
private:
	QWidget *m_qwLeft;
	QWidget *m_qwTopRight;

	QPushButton *m_qlHome;
	QPushButton *m_qlProfile;
	//QPushButton *m_qlFriends;
	QPushButton *m_qlUpload;
	//QPushButton *m_qlSearch;

	QLabel *m_qlImage;
	QLabel *m_qlWelcome;
	QLabel *m_qlRefresh;

	QPushButton *m_qpLogout;
	

	void InitWidgets();
	void BuildConnections();
	

signals:
	void toProfileMode(const QString&);
	void toHome();
	void toSearch();
	void toUpload();
	void logout();
	void refresh();

protected slots:
	void checkValue(int);
	void toProfile();
	
};

#endif