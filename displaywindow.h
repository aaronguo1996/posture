#ifndef _DISPLAYWINDOW_
#define _DISPLAYWINDOW_

#include "MANAGER\ModelVideo.h"
#include "MANAGER\UserManager.h"
#include "posturewindow.h"
#include "globalDefs.h"
#include "displaywidget.h"
#include <QtWidgets\qscrollarea.h>
#include <QtWidgets\qtextedit.h>
#include <QtWidgets\qtextbrowser.h>
#include <QtWidgets\qmessagebox.h>
#include <QtCore\qtimer.h>
#include <ctime>

class DisplayWindow : public PostureWindow
{
	Q_OBJECT
public:
	DisplayWindow(QWidget*, ModelVideo);
	~DisplayWindow();

protected:
	void BuildBottomRight();

private:
	QWidget *m_qwMessage;

	DisplayWidget *m_dwDisplay;

	QLabel *m_qlOutline;
	QLabel *m_qlMsg;
	QLabel *m_qlUser;
	QTextBrowser *m_qtbDesc;

	QPushButton *m_qpbUser;
	QPushButton *m_qpbTag;
	QPushButton *m_qpbSubmit;
	QPushButton *m_qpbLike;
	QPushButton *m_qpbForward;
	QPushButton *m_qpbComment;

	ModelVideo m_mvModel;

	QMessageBox *m_qmbMsg;

	void BuildConnections();
	void BuildMessage();

signals:
	void comment( const ModelVideo&);
	void updateModel(const ModelVideo&);

private slots:
	void likeIt();
	void toComment();
	void forwardIt();
	void toProfile();
};

#endif