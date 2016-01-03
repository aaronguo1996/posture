#include "posturewindow.h"

extern double xscale;
extern double yscale;

PostureWindow::PostureWindow(QWidget *parent)
	:QWidget(parent)
{
	InitWidgets();
	BuildConnections();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_qlImage);
	mainLayout->addSpacing(OFFSET);
	mainLayout->addWidget(m_qlHome);
	mainLayout->addWidget(m_qlProfile);
	//mainLayout->addWidget(m_qlFriends);
	mainLayout->addWidget(m_qlUpload);
	//mainLayout->addWidget(m_qlSearch);
	mainLayout->addStretch();
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpLogout);
	buttonLayout->addStretch();
	mainLayout->addLayout(buttonLayout);
	mainLayout->addStretch();
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setAlignment(Qt::AlignTop);
	mainLayout->setMargin(0);
	m_qwLeft->setLayout(mainLayout); 
	 
	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->addSpacing(SPACE);
	topLayout->addWidget(m_qlWelcome);
	topLayout->addStretch(); 
	topLayout->addWidget(m_qpRefresh); 
	m_qwTopRight->setLayout(topLayout);
	topLayout->setAlignment(Qt::AlignCenter);

	BuildRight();

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(m_qwLeft);
	layout->addWidget(m_qwRight);
	layout->setSpacing(0);
	layout->setMargin(0);
	this->setLayout(layout);
}

PostureWindow::~PostureWindow()
{

}

void PostureWindow::InitWidgets()
{
	m_qwLeft = new QWidget(this);
	m_qwLeft->setObjectName("leftWindow");
	m_qwLeft->setFixedSize(LEFTWINDOW_W*xscale, LEFTWINDOW_H*yscale);

	m_qlImage = new QLabel(m_qwLeft);
	m_qlImage->setPixmap(QPixmap(g_sImgRoot + QString("logicon.png")).scaledToWidth(100*xscale));
	m_qlImage->setAlignment(Qt::AlignCenter);

	m_qlHome = new QPushButton(m_qwLeft);
	m_qlHome->setObjectName("leftFunction");
	m_qlHome->setFixedSize(LEFTFUNCTION_W*xscale, LEFTFUNCTION_H*yscale);
	m_qlHome->setIcon(QIcon(QPixmap(g_sImgRoot + QString("home%1.png").arg(0)).scaled(ICONWIDTH*xscale, ICONHEIGHT*yscale)));
	m_qlHome->setIconSize(QSize(ICONWIDTH,ICONHEIGHT));


	m_qlProfile = new QPushButton(m_qwLeft);
	m_qlProfile->setObjectName("leftFunction");
	m_qlProfile->setFixedSize(LEFTFUNCTION_W*xscale, LEFTFUNCTION_H*yscale);
	m_qlProfile->setIcon(QIcon(QPixmap(g_sImgRoot + QString("profile%1.png").arg(0)).scaled(ICONWIDTH*xscale, ICONHEIGHT*yscale)));
	m_qlProfile->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));

	/*m_qlFriends = new QPushButton(m_qwLeft);
	m_qlFriends->setObjectName("leftFunction");
	m_qlFriends->setIcon(QIcon(QPixmap(g_sImgRoot + QString("friends%1.png").arg(0)).scaled(ICONWIDTH, ICONHEIGHT)));
	m_qlFriends->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
	*/
	m_qlUpload = new QPushButton(m_qwLeft);
	m_qlUpload->setObjectName("leftFunction");
	m_qlUpload->setFixedSize(LEFTFUNCTION_W*xscale, LEFTFUNCTION_H*yscale);
	m_qlUpload->setIcon(QIcon(QPixmap(g_sImgRoot + QString("upload%1.png").arg(0)).scaled(ICONWIDTH*xscale, ICONHEIGHT*yscale)));
	m_qlUpload->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));

	/*m_qlSearch = new QPushButton(m_qwLeft);
	m_qlSearch->setObjectName("leftFunction");
	m_qlSearch->setIcon(QIcon(QPixmap(g_sImgRoot + QString("search%1.png").arg(0)).scaled(ICONWIDTH, ICONHEIGHT)));
	m_qlSearch->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));*/

	m_qpLogout = new QPushButton("Log Out",m_qwLeft);
	m_qpLogout->setObjectName("func");
	m_qpLogout->setFixedSize(FUNC_W*xscale, FUNC_H*yscale);

	m_qwRight = new QWidget(this);
	m_qwRight->setObjectName("rightWindow");
	m_qwRight->setFixedSize(RIGHTWINDOW_W*xscale, RIGHTWINDOW_H*yscale);

	m_qwTopRight = new QWidget(m_qwRight);
	m_qwTopRight->setObjectName("topRightWindow");
	m_qwTopRight->setFixedSize(TOPRIGHTWINDOW_W*xscale, TOPRIGHTWINDOW_H*yscale);

	m_qlWelcome = new QLabel("Share your posture with the world!",m_qwTopRight);
	m_qlWelcome->setObjectName("welcome");
	m_qlWelcome->setFixedSize(WELCOME_W*xscale, WELCOME_H*yscale);

	//m_qlRefresh = new QLabel("Refresh", m_qwTopRight);
	//m_qlRefresh->setObjectName("welcome");
	
	m_qpRefresh = new QPushButton(m_qwTopRight);
	m_qpRefresh->setObjectName("refresh");
	m_qpRefresh->setFixedSize((REFRESH_W+10)*xscale, REFRESH_H*yscale);
	m_qpRefresh->setIcon(QIcon(QPixmap(g_sImgRoot + "refresh0.png").scaled((REFRESH_W+10)*xscale, REFRESH_H*yscale)));
	m_qpRefresh->setIconSize(QSize((REFRESH_W+10)*xscale, REFRESH_H*yscale));
	m_qpRefresh->hide();
}

void PostureWindow::BuildRight()
{
	m_qwBottomRight = new QWidget(m_qwRight);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(m_qwTopRight);
	layout->setSpacing(SPACE);
	layout->addWidget(m_qwBottomRight);
	layout->setMargin(0);
	layout->setAlignment(Qt::AlignTop);
	m_qwRight->setLayout(layout);
}

void PostureWindow::checkValue(int)
{
	qDebug() << "here!";
}

void PostureWindow::BuildConnections()
{
	connect(m_qlProfile, SIGNAL(clicked()), this, SLOT(toProfile()));
	connect(m_qlHome, SIGNAL(clicked()), this, SIGNAL(toHome()));
	//connect(m_qlSearch, SIGNAL(clicked()), this, SIGNAL(toSearch()));
	connect(m_qlUpload, SIGNAL(clicked()), this, SIGNAL(toUpload()));
	connect(m_qpLogout, SIGNAL(clicked()), this, SIGNAL(logout()));
	connect(m_qpRefresh, SIGNAL(clicked()), this, SIGNAL(refresh()));
}

void PostureWindow::toProfile()
{
	emit toProfileMode("");
}

void PostureWindow::CloseFuncs()
{
	m_qlHome->hide();
	m_qlProfile->hide();
	m_qlUpload->hide();
}