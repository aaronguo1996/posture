#ifndef _COMMENTWINDOW_
#define _COMMENTWINDOW_

#include "posturewindow.h"
#include "globalDefs.h"
#include "MANAGER\ModelVideo.h"
#include "MANAGER\UserManager.h"
#include <QtWidgets\qtextedit.h>
#include <QtWidgets\qscrollarea.h>
#include <QtWidgets\qmessagebox.h>
#include <QtCore\qdebug.h>
#include <QtCore\qdatetime.h>

#define MAXPERPAGE 10

class CommentWindow : public PostureWindow
{
	Q_OBJECT
public:
	CommentWindow(QWidget*, ModelVideo);
	~CommentWindow();

protected:
	void BuildBottomRight();

private:
	ModelVideo m_mvModel;

	QWidget *m_qwSingleComment;
	QWidget *m_qwComment;
	QWidget *m_qwMyComment;
	QWidget *m_qwDate;

	QLabel *m_qlCommentTitle;
	QLabel *m_qlCommentTime;
	QLabel *m_qlCommentMon;
	QLabel *m_qlCommentDay;
	QLabel *m_qlCommentCont;
	QLabel *m_qlWords;
	QLabel *m_qlNotify;
	
	QTextEdit *m_qteComment;
	
	QPushButton *m_qpbComment;
	QPushButton *m_qpbReturn;
	QPushButton *m_qpbUsername;
	QPushButton *m_qpbPrev;
	QPushButton *m_qpbNext;

	QScrollArea *m_qsaArea;

	QMessageBox *m_qmbMsg;

	int m_iCurrPage;

	void BuildSingle(int);
	void InitWidgets();
	void BuildConnections();
	void BuildComment();

signals:
	void toDisplay(const ModelVideo&);
	void toProfileMode(const QString&);
	void updateModel(const ModelVideo&);
	void toComment(const ModelVideo&);

private slots:
	void comment();
	void toComment();
	void toReturn();
	void toProfile();
	void prevPage();
	void nextPage();
};

#endif//_COMMENTWINDOW_