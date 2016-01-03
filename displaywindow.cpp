#include "displaywindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

DisplayWindow::DisplayWindow(QWidget *parent,ModelVideo model)
	:PostureWindow(parent)
{
	m_mvModel.m_sDate = model.m_sDate;
	m_mvModel.m_sDescribe = model.m_sDescribe;
	m_mvModel.m_sDirectory = model.m_sDirectory;
	m_mvModel.m_sOutLine = model.m_sOutLine;
	m_mvModel.m_sPublisher = model.m_sPublisher;
	m_mvModel.m_sVideoID = model.m_sVideoID;
	m_mvModel.m_vCommendsName = model.m_vCommendsName;
	m_mvModel.m_vComments = model.m_vComments;
	m_mvModel.m_sFavor = model.m_sFavor;
	m_mvModel.m_sMode = model.m_sMode;
	m_qmbMsg = new QMessageBox(this);
	m_qmbMsg->setObjectName("msg");
	m_qmbMsg->hide();
	BuildBottomRight();
	BuildConnections();
	BuildMessage();
}

DisplayWindow::~DisplayWindow()
{

}

void DisplayWindow::BuildBottomRight()
{
	QHBoxLayout *mainLayout = new QHBoxLayout();
	QVBoxLayout *rightLayout = new QVBoxLayout();
	m_qlOutline = new QLabel(QString(m_mvModel.m_sOutLine.c_str()), this);
	m_qlOutline->setObjectName("displayOutline");
	m_qlOutline->setWordWrap(true);
	m_qlOutline->setMinimumSize(DISPLAYOUTLINE_W*xscale, DISPLAYOUTLINE_H*yscale);
	rightLayout->addStretch();
	rightLayout->addWidget(m_qlOutline);
	rightLayout->addSpacing(SPACE);

	QHBoxLayout *favorLayout = new QHBoxLayout();
	srand(time(NULL));
	m_qpbTag = new QPushButton(m_mvModel.m_sFavor.c_str(), this);//[TODO] change the fixed favor into the info of the video
	m_qpbTag->setObjectName("tag");
	m_qpbTag->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbTag->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.5)")
							.arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	if (QString(m_mvModel.m_sFavor.c_str()) == "")
		m_qpbTag->hide();
	favorLayout->addWidget(m_qpbTag);
	favorLayout->addStretch();
	rightLayout->addLayout(favorLayout);

	QHBoxLayout *funcLayout = new QHBoxLayout();
	m_qpbLike = new QPushButton("Like", this);
	m_qpbLike->setObjectName("like");
	m_qpbLike->setFixedSize(LIKE_W*xscale, LIKE_H*yscale);
	if (m_mvModel.ifCommend(g_umUserManager.GetUsername()))
	{
		m_qpbLike->setIcon(QIcon(g_sImgRoot + "liked.png"));
		m_qpbLike->setText("Liked");
	}
	else
		m_qpbLike->setIcon(QIcon(g_sImgRoot + "like.png"));
	m_qpbLike->setIconSize(QSize(ICONWIDTH*xscale/2, ICONHEIGHT*yscale/2));
	m_qpbForward = new QPushButton("Forward", this);
	m_qpbForward->setObjectName("like");
	m_qpbForward->setFixedSize(LIKE_W*xscale, LIKE_H*yscale);
	m_qpbForward->setIcon(QIcon(g_sImgRoot + "forward.png"));
	m_qpbForward->setIconSize(QSize(ICONWIDTH*xscale / 2, ICONHEIGHT*yscale / 2));
	if (m_mvModel.m_sPublisher == g_umUserManager.GetUsername())
		m_qpbForward->hide();
	m_qpbComment = new QPushButton("Comment", this);
	m_qpbComment->setObjectName("like");
	m_qpbComment->setFixedSize(LIKE_W*xscale, LIKE_H*yscale);
	m_qpbComment->setIcon(QIcon(g_sImgRoot + "comment.png"));
	m_qpbComment->setIconSize(QSize(ICONWIDTH*xscale / 2, ICONHEIGHT*yscale / 2));
	
	funcLayout->addStretch();
	funcLayout->addWidget(m_qpbLike);
	funcLayout->addWidget(m_qpbForward);
	funcLayout->addWidget(m_qpbComment);
	funcLayout->addSpacing(SPACE);

	//m_dwDisplay = new DisplayWidget("display/demo.ms3d", "1", m_qwBottomRight);
	m_dwDisplay = new DisplayWidget(g_sModel + QString(m_mvModel.m_sVideoID.c_str()),m_mvModel.m_sMode.c_str(), m_qwBottomRight);
	m_dwDisplay->setObjectName("display");
	m_dwDisplay->setFixedSize(DISPLAY_W*xscale, DISPLAY_H*yscale);
	m_qlUser = new QLabel("Uploader: ", m_qwBottomRight);
	m_qlUser->setObjectName("name");
	m_qlUser->setFixedSize(NAME_W*3*xscale, NAME_H*yscale);
	m_qpbUser = new QPushButton(m_mvModel.m_sPublisher.c_str(), m_qwBottomRight);
	m_qpbUser->setObjectName("toProfile");
	m_qpbUser->setFixedSize(TOPROFILE_W*xscale, TOPROFILE_H*yscale);
	m_qtbDesc = new QTextBrowser(this);
	m_qtbDesc->setObjectName("desc");
	m_qtbDesc->setFixedSize(DESC_W*xscale, DESC_H*yscale);
	m_qtbDesc->setText(QString("Description: ") + m_mvModel.m_sDescribe.c_str());
	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addWidget(m_qlUser);
	nameLayout->addWidget(m_qpbUser);
	nameLayout->addStretch();
	rightLayout->addStretch();
	rightLayout->addLayout(nameLayout);
	rightLayout->addWidget(m_qtbDesc);
	rightLayout->addStretch();
	rightLayout->addLayout(funcLayout);
	rightLayout->addStretch();

	mainLayout->addWidget(m_dwDisplay);
	mainLayout->addSpacing(SPACE);
	mainLayout->addLayout(rightLayout);
	m_qwBottomRight->setLayout(mainLayout);
}

void DisplayWindow::BuildConnections()
{
	connect(m_qpbLike, SIGNAL(clicked()), this, SLOT(likeIt()));
	connect(m_qpbComment, SIGNAL(clicked()), this, SLOT(toComment()));
	connect(m_qpbForward, SIGNAL(clicked()), this, SLOT(forwardIt()));
	connect(m_qpbUser, SIGNAL(clicked()), this, SLOT(toProfile()));
}

void DisplayWindow::BuildMessage()
{
	m_qwMessage = new QWidget(m_qwBottomRight);
	m_qwMessage->setObjectName("message");
	m_qwMessage->setFixedSize(MESSAGE_W*xscale,MESSAGE_H*yscale);
	m_qlMsg = new QLabel(m_qwMessage);
	m_qlMsg->setObjectName("message");
	m_qwMessage->hide();
}

void DisplayWindow::likeIt()
{
	if (m_qpbLike->text() == "Like")
	{
		if (g_umUserManager.Commend(m_mvModel.m_sVideoID) == SUCCESS)
		{
			g_umUserManager.GetLastVideo(m_mvModel);
			emit updateModel(m_mvModel);

			m_qpbLike->setIcon(QIcon(g_sImgRoot + "liked.png"));
			m_qpbLike->setText("Liked");
		}
		else
		{
			m_qlMsg->setText("Commend Fail, please try again.");
			QTimer *timer = new QTimer();
			timer->start(1000);
			connect(timer, SIGNAL(timeout()), m_qwMessage, SLOT(close()));
			connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
		}
	}
	else if (m_qpbLike->text() == "Liked")
	{
		if (g_umUserManager.UnCommend(m_mvModel.m_sVideoID) == SUCCESS)
		{
			g_umUserManager.GetLastVideo(m_mvModel);
			emit updateModel(m_mvModel);

			m_qpbLike->setIcon(QIcon(g_sImgRoot + "like.png"));
			m_qpbLike->setText("Like");
		}
		else
		{
			m_qlMsg->setText("Uncommend Fail, please try again.");
			QTimer *timer = new QTimer();
			timer->start(1000);
			connect(timer, SIGNAL(timeout()), m_qwMessage, SLOT(close()));
			connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
		}
	}
}

void DisplayWindow::toComment()
{
	emit comment(m_mvModel);
}

void DisplayWindow::forwardIt()
{
	if (g_umUserManager.Share(m_mvModel.m_sVideoID) == SUCCESS)
	{
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		m_qmbMsg->setText("Forward successfully");
		m_qmbMsg->show();
	}
	else
	{
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		m_qmbMsg->setText("Forward fail, please try it again later");
		m_qmbMsg->show();
	}
}

void DisplayWindow::toProfile()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	SourceManager sm;
	UserPro up;
	sm.GetUserProfile(up);
	if (up.m_sUserName.c_str() == btn->text())
		emit toProfileMode("");
	else
		emit toProfileMode(btn->text());
}