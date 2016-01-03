#include "profilewindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

ProfileWindow::ProfileWindow(QWidget *parent,QString username)
	:PostureWindow(parent), m_sUsername(username)
{
	InitWidgets();
	BuildBottomRight();
	if (m_sUsername != "")
	{
		m_qpbEdit->setText("Follow");
		disconnect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(edit()));
		connect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(follow()));
		IsFollowed();
	}
}

ProfileWindow::~ProfileWindow()
{

}

void ProfileWindow::InitWidgets()
{
	m_qlImg = new QLabel(m_qwBottomRight);
	m_qlImg->setPixmap(QPixmap(g_sImgRoot + "person.png").scaled(PICWIDTH*xscale,PICHEIGHT*yscale));

	m_qlNameImg = new QLabel(m_qwBottomRight);
	//m_qlNameImg->setPixmap(QPixmap(g_sImgRoot+"username.png").scaled(ICONWIDTH,ICONHEIGHT));
	m_qlNameTitle = new QLabel("Name:", m_qwBottomRight);
	m_qlNameTitle->setAlignment(Qt::AlignRight);
	m_qlNameTitle->setAlignment(Qt::AlignVCenter);
	m_qlNameTitle->setObjectName("uploadInfo");
	m_qlNameTitle->setFixedSize(100*xscale, UPLOADINFO_H*yscale);
	//m_qlNameTitle->setStyleSheet(QString("min-width:100px;max-width:100px;"));

	if (m_sUsername == "")
		m_qlName = new QLabel( QString(g_umUserManager.GetUsername().c_str()), m_qwBottomRight);
	else
		m_qlName = new QLabel(QString(m_sUsername), m_qwBottomRight);
	m_qlName->setObjectName("upload");
	m_qlName->setFixedSize(UPLOAD_W*xscale, 50*yscale);
	m_qlName->setStyleSheet(QString("border:2px solid #AAAAAA;"));

	m_qlEmailImg = new QLabel(m_qwBottomRight);
	m_qlEmailTitle = new QLabel("Email:", m_qwBottomRight);
	m_qlEmailTitle->setAlignment(Qt::AlignRight);
	m_qlEmailTitle->setAlignment(Qt::AlignVCenter);
	m_qlEmailTitle->setObjectName("uploadInfo");
	m_qlEmailTitle->setFixedSize(100*xscale, UPLOADINFO_H*yscale);
	//m_qlEmailTitle->setStyleSheet(QString("min-width:100px;max-width:100px;"));

	SourceManager sm;
	UserPro up;
	if (m_sUsername == "")
		sm.GetUserProfile(up);
	else
		sm.GetUserProfile(up, m_sUsername.toStdString());
	m_qlEmail = new QLabel(QString(up.m_sEmail.c_str()), m_qwBottomRight);
	//m_qlEmail->setAlignment(Qt::AlignCenter);
	m_qlEmail->setObjectName("upload");
	m_qlEmail->setFixedSize(UPLOAD_W*xscale, 50 * yscale);
	m_qlEmail->setStyleSheet(QString("border:2px solid #AAAAAA;"/*min-height:50px;max-height:50px;"*/));

	m_qpbEdit = new QPushButton("Edit", m_qwBottomRight);
	m_qpbEdit->setObjectName("detail");
	m_qpbEdit->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	
	m_qpbReturn = new QPushButton("Return", m_qwBottomRight);
	m_qpbReturn->setObjectName("detail");
	m_qpbReturn->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbReturn, SIGNAL(clicked()), this, SLOT(toProfile()));
	connect(m_qpbEdit, SIGNAL(clicked()), this, SIGNAL(edit()));

	m_qlTags = new QLabel("Tags:",m_qwBottomRight);
	m_qlTags->setAlignment(Qt::AlignRight);
	m_qlTags->setAlignment(Qt::AlignVCenter);
	m_qlTags->setObjectName("uploadInfo");
	m_qlTags->setFixedSize(100 * xscale, UPLOADINFO_H*yscale);
	//m_qlTags->setStyleSheet(QString("min-width:100px;max-width:100px;"));

	m_qpbAddTag = new QPushButton("Click to add.", m_qwBottomRight);
	m_qpbAddTag->setObjectName("toProfile");
	m_qpbAddTag->setFixedSize(TOPROFILE_W*xscale, TOPROFILE_H*yscale);
	connect(m_qpbAddTag, SIGNAL(clicked()), this, SIGNAL(addTag()));

	m_qmbMsg = new QMessageBox(this);
	m_qmbMsg->setObjectName("msg");
	m_qmbMsg->setMinimumSize(MSG_W*xscale,MSG_H*yscale);
	m_qmbMsg->hide();
}

void ProfileWindow::BuildBottomRight()
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addStretch();
	mainLayout->addWidget(m_qlImg,0,Qt::AlignCenter);
	mainLayout->addSpacing(SPACE*xscale);

	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addSpacing(SPACE*15*xscale);
	//nameLayout->addWidget(m_qlNameImg);
	nameLayout->addWidget(m_qlNameTitle);
	nameLayout->addWidget(m_qlName);
	nameLayout->addStretch();
	mainLayout->addLayout(nameLayout);

	QHBoxLayout *emailLayout = new QHBoxLayout();
	emailLayout->addSpacing(SPACE*15*xscale);
	//emailLayout->addWidget(m_qlEmailImg);
	emailLayout->addWidget(m_qlEmailTitle);
	emailLayout->addWidget(m_qlEmail);
	emailLayout->addStretch();
	mainLayout->addLayout(emailLayout);
	mainLayout->addStretch();

	SourceManager sm;
	UserPro up;
	if (m_sUsername == "")
		sm.GetUserProfile(up);
	else
		sm.GetUserProfile(up, m_sUsername.toStdString());
	QHBoxLayout *tagLayout = new QHBoxLayout();
	tagLayout->addSpacing(SPACE*15*xscale);
	tagLayout->addWidget(m_qlTags);
	if (up.m_vFavors.size() > 0)
	{
		for (int i = 0; i < up.m_vFavors.size(); i++)
		{
			m_qpbTag = new QPushButton(up.m_vFavors[i].c_str(), m_qwBottomRight);
			m_qpbTag->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
			m_qpbTag->setObjectName("tag");
			m_qpbTag->setFixedSize(TAG_W*xscale, TAG_H*yscale);
			tagLayout->addWidget(m_qpbTag);
		}
	}
	if (m_sUsername == "")
		tagLayout->addWidget(m_qpbAddTag);
	else
		m_qpbAddTag->hide();
	tagLayout->addStretch();
	mainLayout->addLayout(tagLayout);
	mainLayout->addStretch();

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbEdit);
	buttonLayout->addWidget(m_qpbReturn);
	buttonLayout->addStretch();
	mainLayout->addLayout(buttonLayout);

	mainLayout->addStretch();
	m_qwBottomRight->setLayout(mainLayout);
}

void ProfileWindow::IsFollowed()
{
	if (m_sUsername != "")
	{
		SourceManager sm;
		UserPro up;
		sm.GetUserProfile(up);
		for (int i = 0; i < up.m_vFollows.size(); i++)
		{
			if (up.m_vFollows[i] == m_sUsername.toStdString())
			{
				m_qpbEdit->setText("Followed");
				disconnect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(follow()));
				connect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(message()));
			}
		}
	}
}

void ProfileWindow::follow()
{
	if (m_sUsername != "")
	{
		if (g_umUserManager.Follow(m_sUsername.toStdString()) == SUCCESS)
		{
			message();
			m_qpbEdit->setText("Followed");
			disconnect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(follow()));
			connect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(message()));
			update();
		}
		else
		{
			m_qmbMsg->setText("Follow failed");
			m_qmbMsg->show();
		}
	}
}

void ProfileWindow::unfollow(QAbstractButton* btn)
{
	if (btn->text() == "OK")
	{
		if (g_umUserManager.UnFollow(m_sUsername.toStdString()) == SUCCESS)
		{
			m_qpbEdit->setText("Follow");
			connect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(follow()));
			disconnect(m_qpbEdit, SIGNAL(clicked()), this, SLOT(message()));
		}
		else
		{
			m_qmbMsg->setText("Unfollow failed, please try it again later.");
			m_qmbMsg->hide();
		}
	}
	else
	{
		m_qmbMsg->close();
	}
}

void ProfileWindow::toProfile()
{
	emit toProfileMode(m_sUsername);
}

void ProfileWindow::message()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btn->text() == "Followed")
	{
		m_qmbMsg = new QMessageBox(this);
		m_qmbMsg->setText("You are unfollowing, click OK to confirm your operation.");
		m_qmbMsg->addButton(QMessageBox::Ok);
		m_qmbMsg->addButton(QMessageBox::Cancel);
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		
		connect(m_qmbMsg, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(unfollow(QAbstractButton*)));

		m_qmbMsg->show();
	}
	else
	{
		m_qmbMsg->setText("Follow successfully");
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		m_qmbMsg->show();
	}
}