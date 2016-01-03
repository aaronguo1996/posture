#include "posture.h"

UserManager g_umUserManager;
QString g_sPwd;
double xscale;
double yscale;

Posture::Posture(QWidget *parent)
	: QMainWindow(parent)
{
	xscale = QApplication::desktop()->width() / 2160.0;
	yscale = QApplication::desktop()->height() / 1440.0;
	if (xscale < yscale)
		yscale = xscale;
	else
		xscale = yscale;
	QFontDatabase::addApplicationFont("fonts/MyriadPro-LightSemiExt.otf");
	qRegisterMetaType<ModelVideo>("ModelVideo");//register the class ModelVideo in qt class to be used in connect function
	ui.setupUi(this);
	this->setWindowIcon(QIcon(":/img/Resources/icon.png"));
	this->setObjectName("main");
	m_lwLogWin = new LogWindow(this,LOG);
	this->setCentralWidget(m_lwLogWin);
	connect(m_lwLogWin, SIGNAL(wait()), this, SLOT(message()));
	connect(m_lwLogWin, SIGNAL(regSuccess()), this, SLOT(logout()));
	m_wtCurrentWin = LOG;
	this->setFixedSize(LOGWINDOW_W*xscale, LOGWINDOW_H*yscale);
	/*m_umwUpWin = new UploadModeWindow(this);
	this->setCentralWidget(m_umwUpWin);
	m_wtCurrentWin = UPLOADMODE;
	connect(m_umwUpWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_umwUpWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_umwUpWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_umwUpWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_umwUpWin, SIGNAL(toUpload(const QString&)), this, SLOT(toUpload(const QString&)));*/
}

Posture::~Posture()
{

}

void Posture::CloseCurrentWindow()
{
	switch (m_wtCurrentWin)
	{
	case REG: case LOG:
		m_lwLogWin->close();
		break;
	case MSG:
		m_qwMsg->close();
		break;
	case WELCOME:
		m_wwPosWin->close();
		break; 
	case PROFILEMODE:
		m_pmwModeWin->close();
		break;
	case PROFILE:
		m_pwProfileWin->close();
		break;
	case DISPLAY:
		m_dwDisWin->close();
		break;
	case SEARCH:
		m_swSearchWin->close();
		break;
	case POSTURELIST:
		m_plwPosWin->close();
		break;
	case UPLOADINFO:
		m_uiwInfoWin->close();
		break; 
	case UPLOADMODE:
		if (m_umwUpWin)
			m_umwUpWin->close();
		break;
	case COMMENT:
		m_cwCommentWin->close();
		break;
	case UPLOAD:
		if (m_uwUploadWin)
			m_uwUploadWin->close();
		break;
	}
}

void Posture::toWelcome(int i)
{
	int count = 0;
	ModelVideo model;
	if (i > models.size() - 1 || i == -1)
	{
		if (i == -1)
			models.clear();
		m_pmPageManager.GetModel(models, i);

		if (i != -1)
		{
			m_iPage = i / MAXATONCE;
			count = models.size() - (m_iPage)*MAXATONCE;
		}
		else
		{
			i = 0;
			m_iPage = 0;
			count = models.size();
		}
	}
	else
	{
		m_iPage = i / MAXATONCE;
		if (models.size() < i + MAXATONCE)
		{
			count = models.size() - i;
		}
		else
		{
			count = MAXATONCE;
		}
	}
	switch (count)
	{
	case 0:
		return;
	case 1:
		m_wwPosWin = new WelcomeWindow(this, count, models[i], model, model, model);
		CloseCurrentWindow();
		break;
	case 2:
		m_wwPosWin = new WelcomeWindow(this, count, models[i], models[i+1], model, model);
		CloseCurrentWindow();
		break;
	case 3:
		m_wwPosWin = new WelcomeWindow(this, count, models[i], models[i+1], models[i+2], model);
		CloseCurrentWindow();
		break;
	case 4:
		m_wwPosWin = new WelcomeWindow(this, count, models[i], models[i+1], models[i+2], models[i+3]);
		CloseCurrentWindow();
		break;
	}
	this->setCentralWidget(m_wwPosWin);
	m_wtCurrentWin = WELCOME;
	modelList.clear();

	connect(m_wwPosWin, SIGNAL(display(const ModelVideo&)), this, SLOT(toDisplay(const ModelVideo&)));
	connect(m_wwPosWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_wwPosWin, SIGNAL(prev()), this, SLOT(prevWelcome()));
	connect(m_wwPosWin, SIGNAL(next()), this, SLOT(nextWelcome()));
	connect(m_wwPosWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_wwPosWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_wwPosWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_wwPosWin, SIGNAL(refresh()), this, SLOT(firstToHome()));
	
	this->setFixedSize(WINDOW_W*xscale, WINDOW_H*yscale);
	this->move((QApplication::desktop()->width() - WINDOW_W*xscale) / 2,
			   (QApplication::desktop()->height() - WINDOW_H*yscale) / 2);
}

void Posture::prevWelcome()
{
	if (m_iPage == 0)
	{
		return;
	}
	else
	{
		toWelcome((m_iPage-1)*MAXATONCE);
		m_iPage--;
	}
}

void Posture::nextWelcome()
{
	toWelcome((++m_iPage)*MAXATONCE);
}

void Posture::toDisplay(const ModelVideo &model)
{
	CloseCurrentWindow();
	modelList.clear();
	m_dwDisWin = new DisplayWindow(this, model);
	m_wtCurrentWin = DISPLAY;
	connect(m_dwDisWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_dwDisWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_dwDisWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_dwDisWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_dwDisWin, SIGNAL(updateModel(const ModelVideo&)), this, SLOT(updateModel(const ModelVideo&)));
	connect(m_dwDisWin, SIGNAL(comment(const ModelVideo&)), this, SLOT(toComment(const ModelVideo&)));
	this->setCentralWidget(m_dwDisWin);
}

void Posture::toHomeWin()
{
	toWelcome(0);
}

void Posture::firstToHome()
{
	models.clear();
	toWelcome(-1);
}

void Posture::toProfileMode(const QString &name)
{
	CloseCurrentWindow();
	modelList.clear();
	m_pmwModeWin = new ProfileModeWindow(this, name);
	m_wtCurrentWin = PROFILEMODE;
	connect(m_pmwModeWin, SIGNAL(toProfile(const QString&)), this, SLOT(toProfile(const QString&)));
	connect(m_pmwModeWin, SIGNAL(toFriends(const QString&)), this, SLOT(toFriends(const QString&)));
	connect(m_pmwModeWin, SIGNAL(toPosture(const QString&)), this, SLOT(toPosture(const QString&)));
	connect(m_pmwModeWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_pmwModeWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_pmwModeWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_pmwModeWin, SIGNAL(logout()), this, SLOT(logout()));
	this->setCentralWidget(m_pmwModeWin);
}

void Posture::toComment(const ModelVideo &model)
{
	CloseCurrentWindow();
	modelList.clear();
	m_cwCommentWin = new CommentWindow(this, model);
	m_wtCurrentWin = COMMENT;
	connect(m_cwCommentWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_cwCommentWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_cwCommentWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_cwCommentWin, SIGNAL(toSearch()), this, SLOT(toSearch()));
	connect(m_cwCommentWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_cwCommentWin, SIGNAL(updateModel(const ModelVideo&)), this, SLOT(updateModel(const ModelVideo&)));
	connect(m_cwCommentWin, SIGNAL(toDisplay(const ModelVideo&)), this, SLOT(toDisplay(const ModelVideo&)));
	connect(m_cwCommentWin, SIGNAL(toComment(const ModelVideo&)), this, SLOT(toComment(const ModelVideo&)));
	this->setCentralWidget(m_cwCommentWin);
}

void Posture::toProfile(const QString &name)
{
	CloseCurrentWindow();
	modelList.clear();
	m_pwProfileWin = new ProfileWindow(this,name);
	m_wtCurrentWin = PROFILE;
	connect(m_pwProfileWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_pwProfileWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_pwProfileWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_pwProfileWin, SIGNAL(edit()), this, SLOT(toProfileEdit()));
	connect(m_pwProfileWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_pwProfileWin, SIGNAL(addTag()), this, SLOT(toTag()));
	this->setCentralWidget(m_pwProfileWin);
}

void Posture::toSearch()
{
	CloseCurrentWindow();
	modelList.clear();
	m_swSearchWin = new SearchWindow(this);
	m_wtCurrentWin = SEARCH;
	connect(m_swSearchWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_swSearchWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_swSearchWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_swSearchWin, SIGNAL(logout()), this, SLOT(logout()));
	//this->setCentralWidget(m_swSearchWin);
}

void Posture::toUploadMode()
{
	CloseCurrentWindow();
	modelList.clear();
	m_umwUpWin = new UploadModeWindow(this);
	m_wtCurrentWin = UPLOADMODE;
	connect(m_umwUpWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_umwUpWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_umwUpWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_umwUpWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_umwUpWin, SIGNAL(toUpload(const QString&)), this, SLOT(toUpload(const QString&)));
	this->setCentralWidget(m_umwUpWin);
}

void Posture::toProfileEdit()
{
	CloseCurrentWindow();
	modelList.clear();
	m_pewEditWin = new ProfileEditWindow(this);
	m_wtCurrentWin = PROFILEEDIT;
	connect(m_pewEditWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_pewEditWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_pewEditWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_pewEditWin, SIGNAL(cancel(const QString&)), this, SLOT(toProfile(const QString&)));
	connect(m_pewEditWin, SIGNAL(success(const QString&)), this, SLOT(toProfile(const QString&)));
	connect(m_pewEditWin, SIGNAL(logout()), this, SLOT(logout()));
	this->setCentralWidget(m_pewEditWin);
}

void Posture::logout()
{
	g_umUserManager.Logout();
	models.clear();
	modelList.clear();
	CloseCurrentWindow();
	m_lwLogWin = new LogWindow(this,LOG);
	this->setCentralWidget(m_lwLogWin);
	connect(m_lwLogWin, SIGNAL(wait()), this, SLOT(message()));
	connect(m_lwLogWin, SIGNAL(regSuccess()), this, SLOT(logout()));
	m_wtCurrentWin = LOG;
	this->setFixedSize(LOGWINDOW_W*xscale, LOGWINDOW_H*yscale);
}

void Posture::toFriends(const QString &name)
{
	CloseCurrentWindow();
	modelList.clear();
	m_fwFriendsWin = new FriendsWindow(this, name);
	m_wtCurrentWin = FRIENDS;
	this->setCentralWidget(m_fwFriendsWin);
	connect(m_fwFriendsWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_fwFriendsWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_fwFriendsWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_fwFriendsWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_fwFriendsWin, SIGNAL(toFriends(const QString&)), this, SLOT(toFriends(const QString&)));
}

void Posture::toPosture(const QString &name)
{
	if (modelList.size() == 0)
		m_iListPage = 0;
	if ((m_iListPage >= modelList.size() / MAXATONCE && modelList.size() % MAXATONCE == 0) || 
		(modelList.size() % MAXATONCE != 0 && m_iListPage > modelList.size() / MAXATONCE))
	{
		if (name != "")
			m_pmPageManager.GetModelByUserID(modelList, name.toStdString(), m_iListPage*MAXATONCE);
		else
			m_pmPageManager.GetModelByUserID(modelList, g_umUserManager.GetUsername(), m_iListPage*MAXATONCE);
	}
	int end = (m_iListPage + 1)*MAXATONCE < modelList.size() ? (m_iListPage + 1)*MAXATONCE : modelList.size();
	m_iListPage = (end - 1) / MAXATONCE;
	m_plwPosWin = new PostureListWindow(this, name, m_iListPage*MAXATONCE, end, modelList);
	CloseCurrentWindow();
	m_wtCurrentWin = POSTURELIST;
	this->setCentralWidget(m_plwPosWin);
	connect(m_plwPosWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_plwPosWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_plwPosWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_plwPosWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_plwPosWin, SIGNAL(display(const ModelVideo&)), this, SLOT(toDisplay(const ModelVideo&)));
	connect(m_plwPosWin, SIGNAL(prev(const QString&)), this, SLOT(prevList(const QString&)));
	connect(m_plwPosWin, SIGNAL(next(const QString&)), this, SLOT(nextList(const QString&)));
}

void Posture::prevList(const QString  &name)
{
	m_iListPage--;
	if (m_iListPage < 0)
	{
		return;
	}
	else
	{
		toPosture(name);
	}
}

void Posture::nextList(const QString &name)
{
	m_iListPage++;
	toPosture(name);
}

void Posture::toUpload(const QString &mode)
{
	CloseCurrentWindow();
	m_uwUploadWin = new UploadWindow(this,mode);
	m_wtCurrentWin = UPLOAD;
	this->setCentralWidget(m_uwUploadWin);
	connect(m_uwUploadWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_uwUploadWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_uwUploadWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_uwUploadWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_uwUploadWin, SIGNAL(toUploadInfo(const QString&)), this, SLOT(toUploadInfo(const QString&)));
}

void Posture::toUploadInfo(const QString &mode)
{
	CloseCurrentWindow();
	m_uiwInfoWin = new UploadInfoWindow(this,mode);
	m_wtCurrentWin = UPLOADINFO;
	this->setCentralWidget(m_uiwInfoWin);
	connect(m_uiwInfoWin, SIGNAL(toHome()), this, SLOT(toHomeWin()));
	connect(m_uiwInfoWin, SIGNAL(toProfileMode(const QString&)), this, SLOT(toProfileMode(const QString&)));
	connect(m_uiwInfoWin, SIGNAL(logout()), this, SLOT(logout()));
	connect(m_uiwInfoWin, SIGNAL(toUpload()), this, SLOT(toUploadMode()));
	connect(m_uiwInfoWin, SIGNAL(toHomeWin()), this, SLOT(firstToHome()));
}

void Posture::message()
{
	CloseCurrentWindow();
	m_qwMsg = new QWidget(this);
	m_wtCurrentWin = MSG;
	QLabel *notify = new QLabel("We are processing your request, please wait...",m_qwMsg);
	notify->setObjectName("error");
	notify->setStyleSheet("min-width:0px;");
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(notify,0,Qt::AlignCenter);
	m_qwMsg->setLayout(layout);
	m_qwMsg->setStyleSheet(QString("background-color:#293047;"));
	this->setCentralWidget(m_qwMsg);
	QTimer *timer = new QTimer;
	timer->start(2000);
	connect(timer, SIGNAL(timeout()), m_qwMsg, SLOT(close()));
	connect(timer, SIGNAL(timeout()), this, SLOT(firstToHome()));
	connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
}

void Posture::toTag()
{
	CloseCurrentWindow();
	m_ctwTagWin = new ChooseTagWindow(this);
	m_wtCurrentWin = TAG;
	this->setCentralWidget(m_ctwTagWin);
	connect(m_ctwTagWin, SIGNAL(addSuccess(const QString&)), this, SLOT(toProfile(const QString&)));
}

void Posture::updateModel(const ModelVideo &model)
{
	for (int i = 0; i < models.size(); i++)
	{
		if (model.m_sVideoID == models[i].m_sVideoID)
		{
			models[i] = model;
		}
	}
	for (int i = 0; i < modelList.size(); i++)
	{
		if (modelList[i].m_sVideoID == model.m_sVideoID)
		{
			modelList[i] = model;
		}
	}
}