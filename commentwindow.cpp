#include "commentwindow.h"

extern UserManager g_umUserManager;
extern double xscale;
extern double yscale;

CommentWindow::CommentWindow(QWidget *parent, ModelVideo  model)
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
	m_iCurrPage = 0;
	InitWidgets();
	BuildBottomRight();
	BuildConnections();
}

CommentWindow::~CommentWindow()
{

}

string toMonth(string mm)
{
	if (mm == "01")
	{
		return "Jan";
	}
	else if (mm == "02")
	{
		return "Feb";
	}
	else if (mm == "03")
	{
		return "Mar";
	}
	else if (mm == "04")
	{
		return "Apr";
	}
	else if (mm == "05")
	{
		return "May";
	}
	else if (mm == "06")
	{
		return "Jun";
	}
	else if (mm == "07")
	{
		return "Jul";
	}
	else if (mm == "08")
	{
		return "Aug";
	}
	else if (mm == "09")
	{
		return "Sep";
	}
	else if (mm == "10")
	{
		return "Oct";
	}
	else if (mm == "11")
	{
		return "Nov";
	}
	else if (mm == "12")
	{
		return "Dec";
	}
	else
	{
		return "";
	}
}

void CommentWindow::BuildSingle(int i)
{
	m_qwSingleComment = new QWidget(m_qwComment);
	m_qwSingleComment->setObjectName("singleComment");
	m_qwSingleComment->setMinimumWidth(SINGLECOMMENT_W*xscale);
	m_qwSingleComment->setMinimumHeight( SINGLECOMMENT_H*yscale);

	string comDate = m_mvModel.m_vComments[i].m_sDate;
	string date = comDate.substr(0,comDate.find_first_of(' '));
	string time = comDate.substr(comDate.find_first_of(' '));
	string year = date.substr(0, date.find_first_of('-'));
	string remainDate = date.substr(date.find_first_of('-')+1);
	string month = remainDate.substr(0,remainDate.find_first_of('-'));
	string day = remainDate.substr(remainDate.find_first_of('-')+1);
	
	m_qwDate = new QWidget(m_qwSingleComment);
	m_qwDate->setObjectName("date");
	m_qwDate->setFixedSize(DATE_W*xscale, DATE_H*yscale);
	m_qlCommentMon = new QLabel(QString(toMonth(month).c_str()), m_qwDate);
	m_qlCommentMon->setObjectName("month");
	m_qlCommentMon->setAlignment(Qt::AlignCenter);
	m_qlCommentDay = new QLabel(QString(day.c_str()), m_qwDate);
	m_qlCommentDay->setObjectName("day");
	m_qlCommentDay->setAlignment(Qt::AlignCenter);
	QVBoxLayout *dateLayout = new QVBoxLayout();
	dateLayout->addWidget(m_qlCommentMon);
	dateLayout->addWidget(m_qlCommentDay);
	m_qwDate->setLayout(dateLayout);

	m_qpbUsername = new QPushButton(m_mvModel.m_vComments[i].m_sCosID.c_str(), m_qwSingleComment);
	m_qpbUsername->setObjectName("toProfile");
	m_qpbUsername->setFixedSize(TOPROFILE_W*xscale, TOPROFILE_H*yscale);
	connect(m_qpbUsername, SIGNAL(clicked()), this, SLOT(toProfile()));
	m_qlCommentCont = new QLabel(m_mvModel.m_vComments[i].m_sContains.c_str(), m_qwSingleComment);
	m_qlCommentCont->setObjectName("commentContent");
	m_qlCommentCont->setFixedSize(COMMENTCONTENT_W*xscale, COMMENTCONTENT_H*yscale);

	m_qlCommentTime = new QLabel(time.c_str(), m_qwSingleComment);
	m_qlCommentTime->setObjectName("commentTime");
	m_qlCommentTime->setFixedSize(COMMENTTIME_W*xscale, COMMENTTIME_H*yscale);

	QVBoxLayout *commentLayout = new QVBoxLayout();
	commentLayout->addWidget(m_qpbUsername);
	commentLayout->addWidget(m_qlCommentCont);
	commentLayout->addStretch();
	commentLayout->addWidget(m_qlCommentTime);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(m_qwDate,0,Qt::AlignTop);
	layout->addSpacing(SPACE);
	layout->addLayout(commentLayout);
	layout->addStretch();
	m_qwSingleComment->setLayout(layout);
}

void CommentWindow::InitWidgets()
{
	m_qlCommentTitle = new QLabel("Comments");
	m_qlCommentTitle->setObjectName("uploadTitle");
	m_qlCommentTitle->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);

	m_qwMyComment = new QWidget(m_qwBottomRight);
	m_qwMyComment->setObjectName("myComment");
	m_qwMyComment->setFixedHeight(MYCOMMENT_H*yscale);
	m_qteComment = new QTextEdit(m_qwBottomRight);
	m_qteComment->setPlaceholderText("Your comments but no more than 140 words");
	m_qteComment->setObjectName("myComment");
	m_qteComment->setFixedHeight(MYCOMMENTEDIT_H*yscale);
	m_qlWords = new QLabel("(no more that 140 words)",m_qwBottomRight);
	m_qlWords->setObjectName("words");
	m_qpbComment = new QPushButton("Comment",m_qwBottomRight);
	m_qpbComment->setObjectName("detail");
	m_qpbComment->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	QVBoxLayout *myLayout = new QVBoxLayout();
	myLayout->addWidget(m_qteComment);
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(m_qlWords);
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_qpbComment);
	myLayout->addLayout(bottomLayout);
	m_qwMyComment->setLayout(myLayout);

	m_qpbReturn = new QPushButton("Return", m_qwBottomRight);
	m_qpbReturn->setObjectName("detail");
	m_qpbReturn->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);

	m_qwComment = new QWidget(m_qwBottomRight);
	m_qwComment->setObjectName("comment");
	m_qwComment->setMinimumWidth(COMMENT_W*xscale);
	m_qsaArea = new QScrollArea(m_qwBottomRight);
	m_qsaArea->setObjectName("comment");
	m_qsaArea->setFixedSize(COMMENTAREA_W*xscale, COMMENTAREA_H*yscale);

	m_qmbMsg = new QMessageBox(this);
	m_qmbMsg->setWindowFlags(Qt::FramelessWindowHint);
	m_qmbMsg->hide();
}

void CommentWindow::BuildBottomRight()
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *titleLayout = new QHBoxLayout();
	titleLayout->addWidget(m_qlCommentTitle);
	titleLayout->addStretch();
	titleLayout->addWidget(m_qpbReturn);
	mainLayout->addLayout(titleLayout);
	mainLayout->addWidget(m_qwMyComment);
	m_qlNotify = new QLabel("No Comments", m_qwBottomRight);
	m_qlNotify->setObjectName("notify");
	m_qlNotify->setFixedSize(NOTIFY_W*xscale, NOTIFY_H*yscale);
	if (m_mvModel.m_vComments.size() == 0)
	{
		m_qlNotify->show();
		mainLayout->addWidget(m_qlNotify);
	}
	else
	{
		m_qlNotify->hide();
		BuildComment();
	}
	mainLayout->addWidget(m_qsaArea);
	mainLayout->addStretch();
	m_qwBottomRight->setLayout(mainLayout);
}

void CommentWindow::BuildComment()
{
	QVBoxLayout *commentLayout = new QVBoxLayout();
	int count = m_mvModel.m_vComments.size() - MAXPERPAGE*(m_iCurrPage) < MAXPERPAGE
		? m_mvModel.m_vComments.size() - MAXPERPAGE*(m_iCurrPage) : MAXPERPAGE;
	for (int i = 0; i < count; i++)
	{
		BuildSingle(i + MAXPERPAGE*(m_iCurrPage));
		commentLayout->addWidget(m_qwSingleComment);
	}
	commentLayout->addStretch();
	m_qpbPrev = new QPushButton("Prev", m_qwComment);
	m_qpbPrev->setObjectName("detail");
	m_qpbPrev->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbNext = new QPushButton("Next", m_qwComment);
	m_qpbNext->setObjectName("detail");
	m_qpbNext->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbPrev, SIGNAL(clicked()), this, SLOT(prevPage()));
	connect(m_qpbNext, SIGNAL(clicked()), this, SLOT(nextPage()));
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbPrev);
	buttonLayout->addWidget(m_qpbNext);
	buttonLayout->addSpacing(SPACE);
	commentLayout->addLayout(buttonLayout);
	m_qwComment->setLayout(commentLayout);
	m_qsaArea->setWidget(m_qwComment);
}

void CommentWindow::BuildConnections()
{
	connect(m_qpbComment, SIGNAL(clicked()), this, SLOT(comment()));
	connect(m_qpbReturn, SIGNAL(clicked()), this, SLOT(toReturn()));
}

void CommentWindow::comment()
{
	if (g_umUserManager.Comment(m_mvModel.m_sVideoID, m_qteComment->toPlainText().toStdString()) == SUCCESS)
	{
		g_umUserManager.GetLastVideo(m_mvModel);
		emit updateModel(m_mvModel);

		m_qteComment->clear();
		m_qmbMsg->setText("Comment Successfully");
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		m_qmbMsg->show();
		connect(m_qmbMsg, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(toComment()));
	}
	else
	{
		m_qmbMsg->setText("Comment Fail");
		m_qmbMsg->setWindowModality(Qt::WindowModal);
		m_qmbMsg->show();
		qDebug() << "oops!";
	}
}

void CommentWindow::toReturn()
{
	emit toDisplay(m_mvModel);
}

void CommentWindow::toComment()
{
	emit toComment(m_mvModel);
}

void CommentWindow::nextPage()
{
	m_iCurrPage++;
	if (m_iCurrPage > (m_mvModel.m_vComments.size() - 1) / MAXPERPAGE)
	{
		m_iCurrPage--;
		return;
	}
	m_qwComment->setAttribute(Qt::WA_DeleteOnClose);
	m_qwComment->close();
	BuildComment();
	m_qsaArea->setWidget(m_qwComment);
}

void CommentWindow::prevPage()
{
	m_iCurrPage--;
	if (m_iCurrPage < 0)
	{
		m_iCurrPage++;
		return;
	}
	m_qwComment->setAttribute(Qt::WA_DeleteOnClose);
	m_qwComment->close();
	BuildComment();
	m_qsaArea->setWidget(m_qwComment);
}

void CommentWindow::toProfile()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	emit toProfileMode(btn->text());
}