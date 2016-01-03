#include "welcomewindow.h"

extern double xscale;
extern double yscale;

WelcomeWindow::WelcomeWindow(QWidget *parent, int size, ModelVideo m1 ,ModelVideo m2, ModelVideo m3, ModelVideo m4)
	:PostureWindow(parent)
{
	m_qvModels.clear();
	switch (size)
	{
	case 0:
		break;
	case 1:
		m_qvModels.push_back(m1);
		break;
	case 2:
		m_qvModels.push_back(m1);
		m_qvModels.push_back(m2);
		break;
	case 3:
		m_qvModels.push_back(m1);
		m_qvModels.push_back(m2);
		m_qvModels.push_back(m3);
		break;
	case 4: default:
		m_qvModels.push_back(m1);
		m_qvModels.push_back(m2);
		m_qvModels.push_back(m3);
		m_qvModels.push_back(m4);
		break;
	}
	BuildBottomRight();
}

WelcomeWindow::~WelcomeWindow()
{

}

void WelcomeWindow::BuildSingle(int i)
{
	m_qwSingle = new QWidget(m_qwBottomRight);
	m_qwSingle->setObjectName("welcomeSingle");
	m_qwSingle->setFixedSize(WELCOMESINGLE_W*xscale,WELCOMESINGLE_H*yscale);

	m_qlImg = new QLabel(m_qwSingle);
	if (QString(m_qvModels[i].m_sFavor.c_str()) != "")
	{
		m_qlImg->setPixmap(QPixmap(g_sImgRoot + QString("%1.jpg").arg(m_qvModels[i].m_sFavor.c_str())).scaled(PICWIDTH*xscale, PICHEIGHT*yscale));
		//qDebug() << "favor:" << m_qvModels[i].m_sFavor.c_str();
	}
	else
		m_qlImg->setPixmap(QPixmap(g_sImgRoot + QString("default.jpg")).scaled(PICWIDTH*xscale, PICHEIGHT*yscale));

	m_qlOutline = new QLabel(QString(m_qvModels[i].m_sOutLine.c_str()), m_qwSingle);
	m_qlOutline->setObjectName("welcomeOutline");
	m_qlOutline->setFixedSize(WELCOMEOUTLINE_W * xscale, WELCOMEOUTLINE_H * yscale);

	QString desc = m_qvModels[i].m_sDescribe.c_str();
	if (desc.length() > 200)
	{
		desc = desc.left(500)+"...";
	}
	m_qlDesc = new QLabel(desc, m_qwSingle);
	m_qlDesc->setObjectName("welcomeDesc");
	m_qlDesc->setFixedSize(WELCOMEDESC_W * xscale, WELCOMEDESC_H * yscale);
	m_qlDesc->setWordWrap(true);

	m_qpDetail = new QPushButton("More details");
	m_qpDetail->setObjectName("detail");
	m_qpDetail->setFixedSize(DETAIL_W * xscale, DETAIL_H * yscale);
	m_qpDetail->setProperty("position",QVariant(i));
	connect(m_qpDetail, SIGNAL(clicked()), this, SLOT(display()));

	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addWidget(m_qlImg, 0, Qt::AlignCenter);
	mainLayout->addSpacing(SPACE);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addStretch();
	layout->addWidget(m_qlOutline,0, Qt::AlignLeft);
	layout->addWidget(m_qlDesc);
	layout->addStretch();
	layout->addWidget(m_qpDetail,0,Qt::AlignRight);
	layout->addStretch();
	layout->setAlignment(Qt::AlignHCenter);
	mainLayout->addLayout(layout);
	mainLayout->addSpacing(SPACE);
	m_qwSingle->setLayout(mainLayout);
}

void WelcomeWindow::BuildBottomRight()
{
	//m_qpRefresh->show();
	connect(m_qpRefresh, SIGNAL(clicked()), this, SIGNAL(refresh()));
	QVBoxLayout *layout = new QVBoxLayout();
	QGridLayout *rightLayout = new QGridLayout();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i * 2 + j < m_qvModels.size())
			{
				BuildSingle(i * 2 + j);
				rightLayout->addWidget(m_qwSingle, i, j);
			}
		}
	}
	rightLayout->setSpacing(SPACE);
	layout->addLayout(rightLayout);

	m_qpPrev = new QPushButton("Prev", m_qwBottomRight);
	m_qpPrev->setObjectName("detail");
	m_qpPrev->setFixedSize(DETAIL_W * xscale, DETAIL_H * yscale);
	connect(m_qpPrev, SIGNAL(clicked()), this, SIGNAL(prev()));
	m_qpNext = new QPushButton("Next", m_qwBottomRight);
	m_qpNext->setObjectName("detail");
	m_qpNext->setFixedSize(DETAIL_W * xscale, DETAIL_H * yscale);
	connect(m_qpNext, SIGNAL(clicked()), this, SIGNAL(next()));
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpPrev);
	buttonLayout->addWidget(m_qpNext);
	buttonLayout->addSpacing(SPACE);

	layout->addLayout(buttonLayout);
	m_qwBottomRight->setLayout(layout);
}

void WelcomeWindow::display()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QVariant val = btn->property("position");
	int pos = val.toInt();
	emit display(m_qvModels[pos]);
}