#include "posturelistwindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

PostureListWindow::PostureListWindow(QWidget *parent,QString name,int start,int end,std::vector<ModelVideo>& video)
	:PostureWindow(parent), m_sUsername(name)
{
	models.clear();
	if (video.size() == 0)
	{
		m_qlNotify = new QLabel("No postures.",m_qwBottomRight);
		m_qlNotify->setObjectName("notify");
		m_qlNotify->setFixedSize(NOTIFY_W*xscale, NOTIFY_H*yscale);
	}
	else
	{
		for (int i = start; i < end; i++)
		{
			models.append(video[i]);
		}
	}
	BuildBottomRight();
}

PostureListWindow::~PostureListWindow()
{

}

void PostureListWindow::InitWidgets(int i)
{
	m_qwSinglePosture = new QWidget(m_qwBottomRight);
	m_qwSinglePosture->setObjectName("welcomeSingle");
	m_qwSinglePosture->setFixedSize(WELCOMESINGLE_W*xscale, WELCOMESINGLE_H*yscale);

	m_qlImg = new QLabel(m_qwSinglePosture);
	if (models[i].m_sFavor != "")
		m_qlImg->setPixmap(QPixmap(g_sImgRoot + QString("%1.jpg").arg(models[i].m_sFavor.c_str())).scaled(PICWIDTH,PICHEIGHT));
	else
		m_qlImg->setPixmap(QPixmap(g_sImgRoot + QString("default.jpg")).scaled(PICWIDTH, PICHEIGHT));
	m_qlOutline = new QLabel(models[i].m_sOutLine.c_str(), m_qwSinglePosture);
	m_qlOutline->setObjectName("welcomeOutline");
	m_qlOutline->setFixedSize(WELCOMEOUTLINE_W*xscale, WELCOMEOUTLINE_H*yscale);
	m_qlDesc = new QLabel(models[i].m_sDescribe.c_str(), m_qwSinglePosture);
	m_qlDesc->setObjectName("welcomeDesc");
	m_qlDesc->setFixedSize(WELCOMEDESC_W*xscale, WELCOMEDESC_H*yscale);
	m_qlDesc->setWordWrap(true);

	if (m_sUsername == "")
	{
		m_qpbOperate = new QPushButton("Delete", m_qwSinglePosture);
		m_qpbOperate->setObjectName("detail");
		m_qpbOperate->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
		m_qpbOperate->setProperty("pos", QVariant(i));
		connect(m_qpbOperate, SIGNAL(clicked()), this, SLOT(deletePos()));
	}
	m_qpbProfile = new QPushButton(QString("Detail"), m_qwSinglePosture);
	m_qpbProfile->setObjectName("detail");
	m_qpbProfile->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbProfile->setProperty("PPP", QVariant(i));
	connect(m_qpbProfile, SIGNAL(clicked()), this, SLOT(toDisplay()));

}

void PostureListWindow::BuildSingle()
{
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addSpacing(SPACE);
	layout->addWidget(m_qlImg);
	QVBoxLayout *rightLayout = new QVBoxLayout();
	rightLayout->addSpacing(SPACE);
	rightLayout->addWidget(m_qlOutline);
	rightLayout->addWidget(m_qlDesc);
	rightLayout->addStretch();
	rightLayout->addWidget(m_qpbProfile);
	if (m_sUsername == "")
		rightLayout->addWidget(m_qpbOperate);
	layout->addLayout(rightLayout);
	m_qwSinglePosture->setLayout(layout);
}

void PostureListWindow::BuildBottomRight()
{
	QVBoxLayout *mainLayout = new QVBoxLayout();

	m_qlTitle = new QLabel("Postures", m_qwBottomRight);
	m_qlTitle->setObjectName("uploadTitle");
	m_qlTitle->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);
	m_qpbReturn = new QPushButton("Return", m_qwBottomRight);
	m_qpbReturn->setObjectName("detail");
	m_qpbReturn->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbReturn, SIGNAL(clicked()), this, SLOT(toProfile()));
	QHBoxLayout *titleLayout = new QHBoxLayout();
	titleLayout->addWidget(m_qlTitle);
	titleLayout->addStretch();
	titleLayout->addWidget(m_qpbReturn);
	mainLayout->addLayout(titleLayout);
	if (models.size() == 0)
		mainLayout->addWidget(m_qlNotify);
	QGridLayout *postureLayout = new QGridLayout();
	
	int imax = models.size() % 2 == 0 ? models.size() / 2 : models.size() / 2 + 1;
	int jmax = models.size() > 2 ? models.size() - 2 : models.size();
	for (int i = 0; i < imax; i++)
	{
		for (int j = 0; j < jmax; j++)
		{
			InitWidgets(i*2+j);
			BuildSingle();
			postureLayout->addWidget(m_qwSinglePosture,i,j);
		}
	}
	mainLayout->addLayout(postureLayout);

	if (imax > 0)
	{
		m_qpbPrev = new QPushButton("Prev", m_qwBottomRight);
		m_qpbPrev->setObjectName("detail");
		m_qpbPrev->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
		connect(m_qpbPrev, SIGNAL(clicked()), this, SLOT(toPrev()));
		m_qpbNext = new QPushButton("Next", m_qwBottomRight);
		m_qpbNext->setObjectName("detail");
		m_qpbNext->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
		connect(m_qpbNext, SIGNAL(clicked()), this, SLOT(toNext()));
		QHBoxLayout *buttonLayout = new QHBoxLayout();
		buttonLayout->addStretch();
		buttonLayout->addWidget(m_qpbPrev);
		buttonLayout->addWidget(m_qpbNext);
		buttonLayout->addSpacing(SPACE);
		if (models.size() == 0)
			mainLayout->addWidget(m_qlNotify);
		mainLayout->addStretch();
		mainLayout->addLayout(buttonLayout);
	}	
	mainLayout->addStretch();

	m_qwBottomRight->setLayout(mainLayout);
}

void PostureListWindow::deletePos()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	g_umUserManager.RemoveShare(models[btn->property("pos").toInt()].m_sVideoID);//[TODO]maybe there should be a notify message
}

void PostureListWindow::toDisplay()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	int pos = btn->property("PPP").toInt();
	emit display(models[pos]);
}

void PostureListWindow::toProfile()
{
	emit toProfileMode(m_sUsername);
}

void PostureListWindow::toPrev()
{
	emit prev(m_sUsername);
}

void PostureListWindow::toNext()
{
	emit next(m_sUsername);
}