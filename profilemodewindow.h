#ifndef _PROFILEMODEWINDOW_
#define _PROFILEMODEWINDOW_

#include "posturewindow.h"
#include "globalDefs.h"

class ProfileModeWindow : public PostureWindow
{
	Q_OBJECT
public:
	ProfileModeWindow(QWidget*,QString);
	~ProfileModeWindow();

protected:
	void BuildBottomRight();

private:
	QWidget *m_qwProfile;
	QWidget *m_qwFriends;
	QWidget *m_qwPosture;

	QLabel *m_qlProfileImg;
	QLabel *m_qlFriendsImg;
	QLabel *m_qlPostureImg;
	QLabel *m_qlProfile;
	QLabel *m_qlFriends;
	QLabel *m_qlPosture;
	QLabel *m_qlProfileDesc;
	QLabel *m_qlFriendsDesc;
	QLabel *m_qlPostureDesc;

	QPushButton *m_qpbProfile;
	QPushButton *m_qpbFriends;
	QPushButton *m_qpbPosture;

	QString m_sUserName;

	void InitWidgets();
	void BuildConnections();

signals:
	void toProfile(const QString&);
	void toPosture(const QString&);
	void toFriends(const QString&);

private slots:
	void toProfile();
	void toPosture();
	void toFriends();
};

#endif