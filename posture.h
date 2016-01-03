#ifndef POSTURE_H
#define POSTURE_H

#include "uploadwindow.h"
#include "MANAGER\PageManager.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <qdesktopwidget.h>
#include <QtCore\qmetatype.h>
#include <QtCore\qtimer.h>
#include <QtGui\qfontdatabase.h>
#include "ui_posture.h"
#include "logwindow.h"
#include "welcomewindow.h"
#include "uploadmodewindow.h"
#include "displaywindow.h"
#include "uploadinfowindow.h"
#include "profilemodewindow.h"
#include "profilewindow.h"
#include "friendswindow.h"
#include "posturelistwindow.h"
#include "searchwindow.h"
#include "commentwindow.h"
#include "profileeditwindow.h"
#include "choosetagwindow.h"

Q_DECLARE_METATYPE(ModelVideo);

class Posture : public QMainWindow
{
	Q_OBJECT

public:
	Posture(QWidget *parent = 0);
	~Posture();

private:
	enum WIN_TYPE{REG,LOG,WELCOME,COMMENT,PROFILEMODE,FRIENDS,PROFILE,MSG,TAG,
			PROFILEEDIT,DISPLAY,SEARCH,POSTURELIST,UPLOADINFO,UPLOAD,UPLOADMODE};
	Ui::postureClass ui;
	LogWindow *m_lwLogWin;
	WelcomeWindow *m_wwPosWin;
	DisplayWindow *m_dwDisWin;
	UploadModeWindow *m_umwUpWin;
	UploadInfoWindow *m_uiwInfoWin;
	ProfileModeWindow *m_pmwModeWin;
	ProfileWindow *m_pwProfileWin;
	FriendsWindow *m_fwFriendsWin;
	PostureListWindow *m_plwPosWin;
	SearchWindow *m_swSearchWin;
	CommentWindow *m_cwCommentWin;
	ProfileEditWindow *m_pewEditWin;
	UploadWindow *m_uwUploadWin;
	QWidget *m_qwMsg;
	ChooseTagWindow *m_ctwTagWin;

	WIN_TYPE m_wtCurrentWin;
	std::vector<ModelVideo> models;
	std::vector<ModelVideo> modelList;
	PageManager m_pmPageManager;
	int m_iPage;
	int m_iListPage;

	void BuildConnections();
	void CloseCurrentWindow();

private slots:
	void toWelcome(int);
	void toDisplay(const ModelVideo&);
	void toComment(const ModelVideo&);
	void toHomeWin();
	void firstToHome();
	void toProfile(const QString&);
	void toSearch();
	void toFriends(const QString&);
	void toPosture(const QString&);
	void toUploadMode();
	void toUpload(const QString&);
	void toUploadInfo(const QString&);
	void toProfileMode(const QString&);
	void toProfileEdit();
	void toTag();
	void nextWelcome();
	void prevWelcome();
	void prevList(const QString&);
	void nextList(const QString&);
	void logout();
	void message();
	void updateModel(const ModelVideo&);
};

#endif // POSTURE_H
