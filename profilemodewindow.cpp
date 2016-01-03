#include "profilemodewindow.h"

extern double xscale;
extern double yscale;

ProfileModeWindow::ProfileModeWindow(QWidget *parent,QString username)
	:PostureWindow(parent), m_sUserName(username)
{
	InitWidgets();
	BuildBottomRight();
	BuildConnections();
}

ProfileModeWindow::~ProfileModeWindow()
{

}

void ProfileModeWindow::InitWidgets()
{
	m_qwFriends = new QWidget(m_qwBottomRight);
	m_qwFriends->setObjectName("profileMode");
	m_qwFriends->setFixedSize(PROFILEMODE_W*xscale, PROFILEMODE_H*yscale);
	m_qwPosture = new QWidget(m_qwBottomRight);
	m_qwPosture->setObjectName("profileMode");
	m_qwPosture->setFixedSize(PROFILEMODE_W*xscale, PROFILEMODE_H*yscale);
	m_qwProfile = new QWidget(m_qwBottomRight);
	m_qwProfile->setObjectName("profileMode");
	m_qwProfile->setFixedSize(PROFILEMODE_W*xscale, PROFILEMODE_H*yscale);

	m_qlFriendsImg = new QLabel(m_qwFriends);
	m_qlFriendsImg->setPixmap(QPixmap(g_sImgRoot+"friends.png").scaled(IMGWIDTH*xscale,IMGHEIGHT*yscale));
	m_qlFriendsImg->setAlignment(Qt::AlignCenter);
	m_qlFriends = new QLabel("Friends", m_qwFriends);
	m_qlFriends->setObjectName("profileTitle");
	m_qlFriends->setFixedSize(PROFILETITLE_W*xscale, PROFILETITLE_H*yscale);
	m_qlFriends->setAlignment(Qt::AlignCenter);
	m_qlFriendsDesc = new QLabel("Show about user's friends and their information", m_qwFriends);
	m_qlFriendsDesc->setWordWrap(true);
	m_qlFriendsDesc->setAlignment(Qt::AlignCenter);
	m_qlFriendsDesc->setObjectName("profileDesc");
	m_qlFriendsDesc->setFixedSize(PROFILEDESC_W*xscale, PROFILEDESC_H*yscale);
	m_qpbFriends = new QPushButton("Go and see",m_qwFriends);
	m_qpbFriends->setObjectName("detail");
	m_qpbFriends->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);

	m_qlPostureImg = new QLabel(m_qwPosture);
	m_qlPostureImg->setPixmap(QPixmap(g_sImgRoot + "posture.png").scaled(IMGWIDTH*xscale,IMGHEIGHT*yscale));
	m_qlPostureImg->setAlignment(Qt::AlignCenter);
	m_qlPosture = new QLabel("Posture", m_qwPosture);
	m_qlPosture->setAlignment(Qt::AlignCenter);
	m_qlPosture->setObjectName("profileTitle");
	m_qlPosture->setFixedSize(PROFILETITLE_W*xscale, PROFILETITLE_H*yscale);
	m_qlPostureDesc = new QLabel("Show about user's postures uploaded to the home page", m_qwPosture);
	m_qlPostureDesc->setWordWrap(true);
	m_qlPostureDesc->setAlignment(Qt::AlignCenter);
	m_qlPostureDesc->setObjectName("profileDesc");
	m_qlPostureDesc->setFixedSize(PROFILEDESC_W*xscale, PROFILEDESC_H*yscale);
	m_qpbPosture = new QPushButton("Go and see", m_qwFriends);
	m_qpbPosture->setObjectName("detail");
	m_qpbPosture->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);

	m_qlProfileImg = new QLabel(m_qwProfile);
	m_qlProfileImg->setPixmap(QPixmap(g_sImgRoot + "profileMode.png").scaled(IMGWIDTH*xscale,IMGHEIGHT*yscale));
	m_qlProfileImg->setAlignment(Qt::AlignCenter);
	m_qlProfile = new QLabel("Profile", m_qwProfile);
	m_qlProfile->setAlignment(Qt::AlignCenter);
	m_qlProfile->setObjectName("profileTitle");
	m_qlProfile->setFixedSize(PROFILETITLE_W*xscale, PROFILETITLE_H*yscale);
	m_qlProfileDesc = new QLabel("Show about user's basic profile", m_qwProfile);
	m_qlProfileDesc->setWordWrap(true);
	m_qlProfileDesc->setAlignment(Qt::AlignCenter);
	m_qlProfileDesc->setObjectName("profileDesc");
	m_qlProfileDesc->setFixedSize(PROFILEDESC_W*xscale, PROFILEDESC_H*yscale); 
	m_qpbProfile = new QPushButton("Go and see", m_qwProfile);
	m_qpbProfile->setObjectName("detail");
	m_qpbProfile->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
}

void ProfileModeWindow::BuildBottomRight()
{
	QHBoxLayout *mainLayout = new QHBoxLayout();

	QVBoxLayout *profileLayout = new QVBoxLayout();
	profileLayout->addSpacing(SPACE);
	profileLayout->addStretch();
	profileLayout->addWidget(m_qlProfileImg, 0, Qt::AlignCenter);
	profileLayout->addStretch();
	profileLayout->addWidget(m_qlProfile, 0,Qt::AlignCenter);
	profileLayout->addWidget(m_qlProfileDesc, 0, Qt::AlignCenter);
	//profileLayout->addStretch();
	profileLayout->addWidget(m_qpbProfile, 0, Qt::AlignCenter);
	profileLayout->addSpacing(SPACE);
	profileLayout->addStretch();
	profileLayout->setMargin(0);
	m_qwProfile->setLayout(profileLayout);


	QVBoxLayout *friendsLayout = new QVBoxLayout();
	friendsLayout->addSpacing(SPACE);
	friendsLayout->addStretch();
	friendsLayout->addWidget(m_qlFriendsImg, 0, Qt::AlignCenter);
	friendsLayout->addStretch();
	friendsLayout->addWidget(m_qlFriends, 0, Qt::AlignCenter);
	friendsLayout->addWidget(m_qlFriendsDesc, 0, Qt::AlignCenter);
	//friendsLayout->addStretch();
	friendsLayout->addWidget(m_qpbFriends, 0, Qt::AlignCenter);
	friendsLayout->addSpacing(SPACE);
	friendsLayout->addStretch();
	friendsLayout->setMargin(0);
	m_qwFriends->setLayout(friendsLayout);

	QVBoxLayout *postureLayout = new QVBoxLayout();
	postureLayout->addSpacing(SPACE);
	postureLayout->addStretch();
	postureLayout->addWidget(m_qlPostureImg, 0, Qt::AlignCenter);
	postureLayout->addStretch();
	postureLayout->addWidget(m_qlPosture, 0, Qt::AlignCenter);
	postureLayout->addWidget(m_qlPostureDesc, 0, Qt::AlignCenter);
	//postureLayout->addStretch();
	postureLayout->addWidget(m_qpbPosture, 0, Qt::AlignCenter);
	postureLayout->addSpacing(SPACE);
	postureLayout->addStretch();
	postureLayout->setMargin(0);
	m_qwPosture->setLayout(postureLayout);

	mainLayout->addWidget(m_qwProfile);
	mainLayout->addWidget(m_qwFriends);
	mainLayout->addWidget(m_qwPosture);
	m_qwBottomRight->setLayout(mainLayout);

}

void ProfileModeWindow::BuildConnections()
{
	connect(m_qpbFriends, SIGNAL(clicked()), this, SLOT(toFriends()));
	connect(m_qpbPosture, SIGNAL(clicked()), this, SLOT(toPosture()));
	connect(m_qpbProfile, SIGNAL(clicked()), this, SLOT(toProfile()));
}

void ProfileModeWindow::toFriends()
{
	emit toFriends(m_sUserName);
}

void ProfileModeWindow::toPosture()
{
	emit toPosture(m_sUserName);
}

void ProfileModeWindow::toProfile()
{
	emit toProfile(m_sUserName);
}