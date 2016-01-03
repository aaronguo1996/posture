#include "choosetagwindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

ChooseTagWindow::ChooseTagWindow(QWidget *parent)
	:PostureWindow(parent)
{
	m_iFavor = 0;
	BuildBottomRight();
}

ChooseTagWindow::~ChooseTagWindow()
{

}

void ChooseTagWindow::InitWidgets()
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
	m_qlTitle = new QLabel("Follow 5 favors\nThen we'll build a custom home feed for you", m_qwBottomRight);
	m_qlTitle->setObjectName("error");
	mainLayout->addStretch();
	mainLayout->addWidget(m_qlTitle);
	mainLayout->addStretch();

	QGridLayout *layout = new QGridLayout();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_qpbFavor = new QPushButton(favors[i*4+j], m_qwBottomRight);
			m_qpbFavor->setObjectName("favorTag");
			m_qpbFavor->setFixedSize(FAVORTAG_W*xscale, FAVORTAG_H*yscale);
			m_qpbFavor->setStyleSheet(QString("QPushButton#favorTag{background-image:url(:/img/Resources/%1.jpg);}\
											   QPushButton#favorTag:hover{background-image:url();background-color:rgba(%2,%3,%4,0.4);}")
											   .arg(favors[i*4+j])
											   .arg(rand() % 255)
											   .arg(rand() % 255)
											   .arg(rand() % 255));
			m_qpbFavor->setProperty("isChoosed", 0);
			connect(m_qpbFavor, SIGNAL(clicked()), this, SLOT(choose()));

			SourceManager sm;
			UserPro up;
			sm.GetUserProfile(up);
			for (int k = 0; k < up.m_vFavors.size(); k++)
			{
				if (up.m_vFavors[k] == favors[i * 4 + j].toStdString())
				{
					m_qpbFavor->setIcon(QIcon(g_sImgRoot + "whiteicon.png"));
					m_qpbFavor->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
					m_qpbFavor->setProperty("isChoosed", 1);
					m_qpbFavor->setStyleSheet(QString("background-image:url();font:bold 15pt 'Myriad Pro Light SemiExt';background-color:rgba(%1, %2, %3, 0.4);")
						.arg(rand() % 255)
						.arg(rand() % 255)
						.arg(rand() % 255));
					m_iFavor++;
				}
			}

			layout->addWidget(m_qpbFavor,i,j,1,1,Qt::AlignCenter);
		}
	}
	layout->setMargin(0);
	layout->setAlignment(Qt::AlignCenter);
	mainLayout->addLayout(layout);
	mainLayout->addStretch();

	m_qpbSubmit = new QPushButton("Done", m_qwBottomRight);
	m_qpbSubmit->setObjectName("detail");
	m_qpbSubmit->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	if (m_iFavor < 5)
		m_qpbSubmit->setDisabled(true);
	connect(m_qpbSubmit, SIGNAL(clicked()), this, SLOT(done()));
	mainLayout->addWidget(m_qpbSubmit);
	mainLayout->addStretch();
	m_qwBottomRight->setLayout(mainLayout);
}

void ChooseTagWindow::BuildBottomRight()
{
	InitWidgets();
}

void ChooseTagWindow::choose()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btn->property("isChoosed").toInt() == 0)
	{
		btn->setIcon(QIcon(g_sImgRoot+"whiteicon.png"));
		btn->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
		btn->setStyleSheet(QString("background-image:url();font:bold 15pt 'Myriad Pro Light SemiExt';background-color:rgba(%1, %2, %3, 0.4);")
							.arg(rand() % 255)
							.arg(rand() % 255)
							.arg(rand() % 255));
		btn->setProperty("isChoosed", 1);
		m_sFavor.push_back(btn->text());
		for (int i = 0; i < m_sFavorRemove.size(); i++)
		{
			if (btn->text() == m_sFavorRemove[i])
			{
				m_sFavorRemove.erase(m_sFavorRemove.begin() + i);
			}
		}
		m_iFavor++;
		if (m_iFavor >= 5)
			m_qpbSubmit->setEnabled(true);
	}
	else
	{
		btn->setIcon(QIcon(""));
		btn->setIconSize(QSize(0, 0));
		btn->setProperty("isChoosed", 0);
		btn->setStyleSheet(QString("QPushButton#favorTag{background-image:url(:/img/Resources/%1.jpg);}\
									QPushButton#favorTag:hover{background-image:url();background-color:rgba(%2,%3,%4,0.4);}")
									.arg(btn->text())
									.arg(rand() % 255)
									.arg(rand() % 255)
									.arg(rand() % 255));
		m_sFavorRemove.push_back(btn->text());
		for (int i = 0; i < m_sFavor.size(); i++)
		{
			if (btn->text() == m_sFavor[i])
			{
				m_sFavor.erase(m_sFavor.begin() + i);
			}
		}
		m_iFavor--;
		if (m_iFavor < 5)
			m_qpbSubmit->setDisabled(true);
	}
}

void ChooseTagWindow::done()
{
	for (int i = 0; i < m_sFavor.size(); i++)
	{
		if (g_umUserManager.AddFavor(m_sFavor[i].toStdString()) == FAVORERRO)
		{
			qDebug() << "Oops!";
		}
	}
	for (int i = 0; i < m_sFavorRemove.size(); i++)
	{
		if (g_umUserManager.RemoveFavor(m_sFavorRemove[i].toStdString()) == FAVORERRO)
		{
			qDebug() << "Oops!";
		}
	}
	emit addSuccess("");
}