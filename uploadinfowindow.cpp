#include "uploadinfowindow.h"
#include <qtimer.h>
extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

UploadInfoWindow::UploadInfoWindow(QWidget *parent,QString mode)
:PostureWindow(parent), m_sHandMode(mode)
{
	BuildBottomRight();
}

UploadInfoWindow::~UploadInfoWindow()
{

}

void UploadInfoWindow::BuildBottomRight()
{
	InitWidgets();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_qlTitle);

	QHBoxLayout *outlineLayout = new QHBoxLayout();
	//outlineLayout->addSpacing(SPACE);
	outlineLayout->addStretch();
	outlineLayout->addWidget(m_qlOutline);
	outlineLayout->addWidget(m_qleOutline);
	outlineLayout->addStretch();
	mainLayout->addLayout(outlineLayout);

	QHBoxLayout *descLayout = new QHBoxLayout();
	descLayout->addStretch();
	//descLayout->addSpacing(SPACE);
	descLayout->addWidget(m_qlDesc);
	descLayout->addWidget(m_qteDesc);
	descLayout->addStretch();
	mainLayout->addLayout(descLayout);

	QHBoxLayout *tagLayout = new QHBoxLayout();
	m_qglTagChoosed = new QGridLayout(m_qwTagChoosed);
	m_qglTagToChoose = new QGridLayout(m_qwTagToChoose);
	m_qglTagToChoose->addWidget(m_qpbCard, 0, 0, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbDance, 0, 1, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbFairy, 0, 2, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbGame, 0, 3, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbMagic, 1, 0, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbMartial, 1, 1, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbPencil, 1, 2, Qt::AlignCenter);
	m_qglTagToChoose->addWidget(m_qpbStory, 1, 3, Qt::AlignCenter);
	m_qwTagChoosed->setLayout(m_qglTagChoosed);
	m_qwTagToChoose->setLayout(m_qglTagToChoose);
	//tagLayout->addSpacing(SPACE);
	tagLayout->addStretch();
	tagLayout->addWidget(m_qlTags);
	tagLayout->addWidget(m_qwTagChoosed);
	tagLayout->addWidget(m_qwTagToChoose);
	tagLayout->addStretch();
	mainLayout->addLayout(tagLayout);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbSubmit);
	buttonLayout->addWidget(m_qpbCancel);
	buttonLayout->addSpacing(SPACE);
	mainLayout->addLayout(buttonLayout);

	m_qwBottomRight->setLayout(mainLayout);
}

void UploadInfoWindow::InitWidgets()
{
	m_qlTitle = new QLabel("Please fill in the posture information.", m_qwBottomRight);
	m_qlTitle->setObjectName("uploadTitle");
	m_qlTitle->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);

	m_qlOutline = new QLabel("Outline",m_qwBottomRight);
	m_qlOutline->setObjectName("uploadInfo");
	m_qlOutline->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qleOutline = new QLineEdit(m_qwBottomRight);
	m_qleOutline->setObjectName("uploadLine");
	m_qleOutline->setFixedSize(UPLOADLINE_W*xscale, UPLOADLINE_H*yscale);
	m_qleOutline->setPlaceholderText("Input outline of your posture, no more than 8 characters");
	m_qleOutline->setMaxLength(8);

	m_qlDesc = new QLabel("Description", m_qwBottomRight);
	m_qlDesc->setObjectName("uploadInfo");
	m_qlDesc->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qteDesc = new QTextEdit(m_qwBottomRight);
	m_qteDesc->setObjectName("uploadText");
	m_qteDesc->setFixedSize(UPLOADTEXT_W*xscale, UPLOADTEXT_H*yscale);
	m_qteDesc->setPlaceholderText("Input brief description of your posture...");

	m_qlTags = new QLabel("Tags", m_qwBottomRight);
	m_qlTags->setObjectName("uploadInfo");
	m_qlTags->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qwTagChoosed = new QWidget(m_qwBottomRight);
	m_qwTagChoosed->setObjectName("tag");
	m_qwTagChoosed->setFixedSize(TAGWIDGET_W*xscale, TAGWIDGET_H*yscale);
	m_qwTagToChoose = new QWidget(m_qwBottomRight);
	m_qwTagToChoose->setObjectName("tag");
	m_qwTagToChoose->setFixedSize(TAGWIDGET_W*xscale, TAGWIDGET_H*yscale);
	m_qlNotify = new QLabel("Click from right to add tags for your posture.",m_qwTagChoosed);
	m_qlNotify->setWordWrap(true);
	m_qlNotify->setObjectName("notify");
	m_qlNotify->setFixedSize(NOTIFY_W*xscale, NOTIFY_H*yscale);

	srand(time(NULL));
	m_qpbCard = new QPushButton("card", m_qwTagToChoose);
	m_qpbCard->setObjectName("tag");
	m_qpbCard->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbCard->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbCard, SIGNAL(clicked()), this, SLOT(addTag()));

	m_qpbDance = new QPushButton("dance", m_qwTagToChoose);
	m_qpbDance->setObjectName("tag");
	m_qpbDance->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbDance->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbDance, SIGNAL(clicked()), this, SLOT(addTag()));

	m_qpbFairy = new QPushButton("fairy", m_qwTagToChoose);
	m_qpbFairy->setObjectName("tag");
	m_qpbFairy->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbFairy->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbFairy, SIGNAL(clicked()), this, SLOT(addTag())); 
	
	m_qpbGame = new QPushButton("game", m_qwTagToChoose);
	m_qpbGame->setObjectName("tag");
	m_qpbGame->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbGame->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbGame, SIGNAL(clicked()), this, SLOT(addTag())); 
	
	m_qpbMagic = new QPushButton("magic", m_qwTagToChoose);
	m_qpbMagic->setObjectName("tag");
	m_qpbMagic->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbMagic->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbMagic, SIGNAL(clicked()), this, SLOT(addTag())); 
	
	m_qpbMartial = new QPushButton("martial", m_qwTagToChoose);
	m_qpbMartial->setObjectName("tag");
	m_qpbMartial->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbMartial->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbMartial, SIGNAL(clicked()), this, SLOT(addTag())); 
	
	m_qpbPencil = new QPushButton("pencil", m_qwTagToChoose);
	m_qpbPencil->setObjectName("tag");
	m_qpbPencil->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbPencil->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbPencil, SIGNAL(clicked()), this, SLOT(addTag())); 
	
	m_qpbStory = new QPushButton("story", m_qwTagToChoose);
	m_qpbStory->setObjectName("tag");
	m_qpbStory->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbStory->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	connect(m_qpbStory, SIGNAL(clicked()), this, SLOT(addTag()));

	m_qpbSubmit = new QPushButton("Submit", m_qwBottomRight);
	m_qpbSubmit->setObjectName("detail");
	m_qpbSubmit->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbCancel = new QPushButton("Cancel", m_qwBottomRight);
	m_qpbCancel->setObjectName("detail");
	m_qpbCancel->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbSubmit, SIGNAL(clicked()), this, SLOT(submit()));
	connect(m_qpbCancel, SIGNAL(clicked()), this, SIGNAL(toUpload()));

	m_qpbChoose = new QPushButton("", m_qwTagChoosed);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(m_qpbChoose);
	m_qwTagChoosed->setLayout(layout);
	m_qpbChoose->hide();
}

void UploadInfoWindow::submit()
{
	string outline = m_qleOutline->text().toStdString();
	string describe = m_qteDesc->toPlainText().toStdString();
	string tag = m_qpbChoose->text().toStdString();
	string path = "real_Joints_Pos.txt";
	if (g_umUserManager.upload(outline, describe, tag, path, m_sHandMode.toStdString()) == SUCCESS)
	{
		QTimer *timer = new QTimer();
		timer->start(1000);
		connect(timer, SIGNAL(timeout()), this, SIGNAL(toHomeWin()));
		connect(timer, SIGNAL(timeout()), this, SLOT(stop()));
	}
}

void UploadInfoWindow::addTag()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	removeTag();
	m_qlNotify->hide();
	m_qpbChoose->setText(btn->text());
	m_qpbChoose->setObjectName("tag");
	m_qpbChoose->setFixedSize(TAG_W*xscale, TAG_H*yscale);
	m_qpbChoose->setStyleSheet(QString("background-color:rgba(%1,%2,%3,0.4);").arg(rand() % 255).arg(rand() % 255).arg(rand() % 255));
	m_qpbChoose->show();
	btn->hide();
	connect(m_qpbChoose, SIGNAL(clicked()), this, SLOT(removeTag()));
}

void UploadInfoWindow::removeTag()
{
	if (m_qpbChoose->text() != "")
	{
		if (m_qpbChoose->text() == "card")
		{
			m_qpbCard->show();
		}
		else if (m_qpbChoose->text() == "magic")
		{
			m_qpbMagic->show();
		}
		else if (m_qpbChoose->text() == "dance")
		{
			m_qpbDance->show();
		}
		else if (m_qpbChoose->text() == "pencil")
		{
			m_qpbPencil->show();
		}
		else if (m_qpbChoose->text() == "story")
		{
			m_qpbStory->show();
		}
		else if (m_qpbChoose->text() == "fairy")
		{
			m_qpbFairy->show();
		}
		else if (m_qpbChoose->text() == "martial")
		{
			m_qpbMartial->show();
		}
		else if (m_qpbChoose->text() == "game")
		{
			m_qpbGame->show();
		}
	}
	m_qpbChoose->hide();
}