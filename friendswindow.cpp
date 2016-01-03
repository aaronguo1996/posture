#include "friendswindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

FriendsWindow::FriendsWindow(QWidget *parent,QString username)
	:PostureWindow(parent), m_sUsername(username)
{
	m_iPage = 0;
	m_qmbMsg = new QMessageBox(this);
	m_qmbMsg->hide();
	BuildBottomRight();
	layout = new QHBoxLayout();
	layout->addWidget(m_qwFriends);
	layout->setMargin(0);
	m_qwBottomRight->setLayout(layout);
}

FriendsWindow::~FriendsWindow()
{

}

void FriendsWindow::InitWidgets(int i)
{
	SourceManager sm;
	UserPro up;
	sm.GetUserProfile(up, m_upUp.m_vFollows[i]);

	m_qwSingleFriend = new QWidget(m_qwBottomRight);
	m_qwSingleFriend->setObjectName("singleFriend");
	m_qwSingleFriend->setMinimumHeight(SINGLEFRIEND_H*yscale);

	m_qlNo = new QLabel(QString("%1").arg(i+1), m_qwSingleFriend);
	m_qlNo->setObjectName("friend");
	m_qlNo->setFixedSize(FRIEND_W*xscale, FRIEND_H*yscale);
	m_qpbName = new QPushButton(up.m_sUserName.c_str(), m_qwSingleFriend);
	m_qpbName->setObjectName("toProfile");
	m_qpbName->setFixedSize(TOPROFILE_W*xscale, TOPROFILE_H*yscale);
	m_qpbName->setStyleSheet("font-weight:bold;");
	connect(m_qpbName, SIGNAL(clicked()), this, SLOT(toProfile()));
	m_qlEmail = new QLabel(up.m_sEmail.c_str(), m_qwSingleFriend);
	m_qlEmail->setObjectName("friendName");
	m_qlEmail->setAlignment(Qt::AlignCenter);
	m_qlEmail->setFixedSize(FRIENDNAME_W*xscale, FRIENDNAME_W*yscale);

	if (m_sUsername == "")
	{
		m_qpbOperate = new QPushButton("Delete", m_qwSingleFriend);
		m_qpbOperate->setObjectName("friendButton");
		m_qpbOperate->setFixedSize(FRIENDBUTTON_W*xscale, FRIENDBUTTON_H*yscale);
		m_qpbOperate->setProperty("pos", QVariant(i));
	}
	
}

void FriendsWindow::BuildSingle()
{
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addSpacing(SPACE);
	layout->addWidget(m_qlNo);
	layout->addWidget(m_qpbName);
	layout->addSpacing(SPACE);
	layout->addWidget(m_qlEmail);
	layout->addStretch();
	if (m_sUsername == "")
	{
		layout->addWidget(m_qpbOperate);
		connect(m_qpbOperate, SIGNAL(clicked()), this, SLOT(message()));
	}
	m_qwSingleFriend->setLayout(layout);
}

void FriendsWindow::BuildBottomRight()
{
	m_qwFriends = new QWidget(m_qwBottomRight);
	QVBoxLayout *mainLayout = new QVBoxLayout();

	m_qlFriendsTitle = new QLabel("Friends");
	m_qlFriendsTitle->setObjectName("uploadTitle");
	m_qlFriendsTitle->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);
	m_qpbReturn = new QPushButton("Return", m_qwFriends);
	m_qpbReturn->setObjectName("detail");
	m_qpbReturn->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbReturn, SIGNAL(clicked()), this, SLOT(toProfileB()));
	QHBoxLayout *titleLayout = new QHBoxLayout();
	titleLayout->addWidget(m_qlFriendsTitle);
	titleLayout->addStretch();
	titleLayout->addWidget(m_qpbReturn);
	mainLayout->addLayout(titleLayout);

	SourceManager sm;
	m_upUp = UserPro();
	if (m_sUsername != "")
		sm.GetUserProfile(m_upUp, m_sUsername.toStdString());
	else
		sm.GetUserProfile(m_upUp);
	if (m_upUp.m_vFollows.size() > 0)
	{
		int max = FRIENDPERPAGE < m_upUp.m_vFollows.size() - m_iPage*FRIENDPERPAGE ? FRIENDPERPAGE : m_upUp.m_vFollows.size() - m_iPage*FRIENDPERPAGE;
		for (int i = 0; i < max; i++)
		{
			InitWidgets(m_iPage*FRIENDPERPAGE+i);
			BuildSingle();
			mainLayout->addWidget(m_qwSingleFriend);
		}
		m_qpbPrev = new QPushButton("Prev", m_qwFriends);
		m_qpbPrev->setObjectName("detail");
		m_qpbPrev->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
		connect(m_qpbPrev, SIGNAL(clicked()), this, SLOT(prevPage()));
		m_qpbNext = new QPushButton("Next", m_qwFriends);
		m_qpbNext->setObjectName("detail");
		m_qpbNext->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
		connect(m_qpbNext, SIGNAL(clicked()), this, SLOT(nextPage()));
		QHBoxLayout *buttonLayout = new QHBoxLayout();
		buttonLayout->addStretch();
		buttonLayout->addWidget(m_qpbPrev);
		buttonLayout->addWidget(m_qpbNext);
		buttonLayout->addStretch();
		mainLayout->addStretch();
		mainLayout->addLayout(buttonLayout);
		mainLayout->addStretch();
	}
	else
	{
		m_qlNotify = new QLabel("No Friends.", m_qwFriends);
		m_qlNotify->setObjectName("notify");
		m_qlNotify->setFixedHeight(NOTIFY_H*yscale);
		m_qlNotify->setMinimumWidth(NOTIFY_W*xscale);
		mainLayout->addWidget(m_qlNotify);
	}
	m_qwFriends->setLayout(mainLayout);
	
}

void FriendsWindow::message()
{
	m_qmbMsg = new QMessageBox(this);
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	m_iPosToDelete = btn->property("pos").toInt();
	m_qmbMsg->setText("Are you sure to delete this friend?");
	m_qmbMsg->addButton(QMessageBox::Ok);
	m_qmbMsg->addButton(QMessageBox::Cancel);
	connect(m_qmbMsg, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(deleteFriend(QAbstractButton*)));
	m_qmbMsg->show();
}

void FriendsWindow::deleteFriend(QAbstractButton* btn)
{
	if (btn->text() == "OK")
	{
		g_umUserManager.UnFollow(m_upUp.m_vFollows[m_iPosToDelete]);
		emit toFriends(m_sUsername);
	}
	else
		m_qmbMsg->close();

}

void FriendsWindow::toProfile()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	emit toProfileMode(btn->text());
}

void FriendsWindow::toProfileB()
{
	emit toProfileMode(m_sUsername);
}

void FriendsWindow::prevPage()
{
	if (m_iPage == 0)
		return;
	else
		m_iPage--;
	delete m_qwFriends;
	BuildBottomRight();
	layout->addWidget(m_qwFriends);
	layout->setMargin(0);
}

void FriendsWindow::nextPage()
{
	if ((m_iPage+1)*FRIENDPERPAGE >= m_upUp.m_vFollows.size())
		return;
	else
		m_iPage++;
	delete m_qwFriends;
	BuildBottomRight();
	layout->addWidget(m_qwFriends);
	layout->setMargin(0);
	//m_qwBottomRight->setLayout(layout);
}