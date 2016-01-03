#ifndef _FRIENDSWINDOW_
#define _FRIENDSWINDOW_

#include "MANAGER\UserManager.h"
#include "MANAGER\SourceManager.h"
#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qscrollarea.h>
#include <QtWidgets\qmessagebox.h>

#define FRIENDPERPAGE 4

class FriendsWindow : public PostureWindow
{
	Q_OBJECT
public:
	FriendsWindow(QWidget*,QString);
	~FriendsWindow();

protected:
	void BuildBottomRight();

private:
	QWidget *m_qwSingleFriend;
	QWidget *m_qwFriends;

	QLabel *m_qlFriendsTitle;
	QLabel *m_qlNo;
	QLabel *m_qlEmail;
	QLabel *m_qlNotify;
	
	QPushButton *m_qpbName;
	QPushButton *m_qpbOperate;
	QPushButton *m_qpbPrev;
	QPushButton *m_qpbNext;
	QPushButton *m_qpbReturn;

	QString m_sUsername;
	UserPro m_upUp;

	QMessageBox *m_qmbMsg;
	QHBoxLayout *layout;

	int m_iPage;
	int m_iPosToDelete;
	void InitWidgets(int i);
	void BuildSingle();

signals:
	void toFriends(const QString&);

private slots:
	void deleteFriend(QAbstractButton*);
	void toProfile();
	void toProfileB();
	void prevPage();
	void nextPage();
	void message();
};

#endif//_FRIENDSWINDOW_