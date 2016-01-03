#include "logwindow.h"

extern UserManager g_umUserManager;
extern QString g_sPwd;
extern double xscale;
extern double yscale;

LogWindow::LogWindow(QWidget *parent,int mode)
	:QWidget(parent)
{
	//this->setObjectName("logWindow");
	this->setFixedSize(LOGWINDOW_W*xscale, LOGWINDOW_H*yscale);
	InitWidgets();
	BuildConnections();
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_qlIcon);
	m_qlIcon->setAlignment(Qt::AlignCenter);
	mainLayout->addStretch();
	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addStretch();
	nameLayout->addWidget(m_qlNameIcon);
	nameLayout->addWidget(m_qleName);
	nameLayout->addStretch();
	mainLayout->addLayout(nameLayout);
	mainLayout->addSpacing(30*yscale);
	QHBoxLayout *pwdLayout = new QHBoxLayout();
	pwdLayout->addStretch();
	pwdLayout->addWidget(m_qlPwdIcon);
	pwdLayout->addWidget(m_qlePwd);
	pwdLayout->addStretch();
	mainLayout->addLayout(pwdLayout);
	mainLayout->addSpacing(30*yscale);
	QHBoxLayout *pwdcLayout = new QHBoxLayout();
	pwdcLayout->addStretch();
	pwdcLayout->addWidget(m_qlPwdcIcon);
	pwdcLayout->addWidget(m_qlePwdc);
	pwdcLayout->addStretch();
	mainLayout->addLayout(pwdcLayout);
	mainLayout->addSpacing(30*yscale);
	QHBoxLayout *emailLayout = new QHBoxLayout();
	emailLayout->addStretch();
	emailLayout->addWidget(m_qlEmailIcon);
	emailLayout->addWidget(m_qleEmail);
	emailLayout->addStretch();
	mainLayout->addLayout(emailLayout);
	mainLayout->addStretch();
	QHBoxLayout *errorLayout = new QHBoxLayout();
	errorLayout->addStretch();
	errorLayout->addWidget(m_qlErrorMsg);
	errorLayout->addStretch();
	mainLayout->addLayout(errorLayout);
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpCommitButton);
	buttonLayout->addStretch();
	mainLayout->addStretch();
	mainLayout->addLayout(buttonLayout);
	QHBoxLayout *logLayout = new QHBoxLayout();
	logLayout->addStretch();
	logLayout->addWidget(m_qlToReg);
	logLayout->addWidget(m_qpToLogButton);
	logLayout->addStretch();
	mainLayout->addLayout(logLayout);
	mainLayout->addStretch();
	this->setLayout(mainLayout);
	if (mode == 0)
	{
		toReg();
	}
	else if (mode == 1)
	{
		toLog();
	}
}

LogWindow::~LogWindow()
{

}

void LogWindow::InitWidgets()
{
	m_qlIcon = new QLabel(this);
	m_qlIcon->setPixmap(QPixmap(QString(g_sImgRoot+"logicon.png")).scaledToWidth(200*xscale));
	m_qlNameIcon = new QLabel(this);
	m_qlNameIcon->setPixmap(QPixmap(QString(g_sImgRoot + "username.png")).scaled(50*xscale, 50*yscale));
	m_qlNameIcon->setAlignment(Qt::AlignCenter);
	m_qleName = new QLineEdit(this);
	m_qleName->setObjectName("logLineEdit");
	m_qleName->setFixedSize(LOGLINEEDIT_W*xscale, LOGLINEEDIT_H*yscale);
	qDebug() << xscale << yscale;
	qDebug() << LOGLINEEDIT_W << LOGWINDOW_W;
	m_qleName->setPlaceholderText("Username");
	m_qleName->setToolTip("Sepcial charaters are not allowed except the underline.");
	m_qlPwdIcon = new QLabel(this);
	m_qlPwdIcon->setPixmap(QPixmap(QString(g_sImgRoot + "pwd.png")).scaled(50*xscale, 50*yscale));
	m_qlePwd = new QLineEdit(this);
	m_qlePwd->setObjectName("logLineEdit");
	m_qlePwd->setFixedSize(LOGLINEEDIT_W*xscale, LOGLINEEDIT_H*yscale);
	m_qlePwd->setEchoMode(QLineEdit::Password);
	m_qlePwd->setPlaceholderText("Password");
	m_qlePwd->setToolTip("At least 4 characters.");
	m_qlPwdcIcon = new QLabel(this);
	m_qlPwdcIcon->setPixmap(QPixmap(QString(g_sImgRoot + "pwdc.png")).scaled(50*xscale, 50*yscale));
	m_qlePwdc = new QLineEdit(this);
	m_qlePwdc->setObjectName("logLineEdit");
	m_qlePwdc->setFixedSize(LOGLINEEDIT_W*xscale, LOGLINEEDIT_H*yscale);
	m_qlePwdc->setEchoMode(QLineEdit::Password);
	m_qlePwdc->setPlaceholderText("Password Confirm");
	m_qlePwdc->setToolTip("Input your password again.");
	m_qlEmailIcon = new QLabel("Email", this);
	m_qlEmailIcon->setPixmap(QPixmap(QString(g_sImgRoot + "email.png")).scaled(50*xscale, 50*yscale));
	m_qleEmail = new QLineEdit(this);
	m_qleEmail->setObjectName("logLineEdit");
	m_qleEmail->setFixedSize(LOGLINEEDIT_W*xscale, LOGLINEEDIT_H*yscale);
	m_qleEmail->setPlaceholderText("Email");
	m_qleEmail->setToolTip("Input your frequently used email.");
	m_qlErrorMsg = new QLabel(this);
	m_qpCommitButton = new QPushButton("Register", this);
	m_qpCommitButton->setObjectName("logCommit");
	m_qpCommitButton->setFixedSize(LOGCOMMIT_W*xscale, LOGCOMMIT_H*yscale);
	m_qlToReg = new QLabel("If you already have an account, click here to", this);
	m_qlToReg->setObjectName("toReg");
	m_qlToReg->setMinimumWidth(TOREG_W*xscale);
	m_qlToReg->setFixedHeight( TOREG_H*yscale);
	m_qlToReg->setAlignment(Qt::AlignCenter);
	m_qpToLogButton = new QPushButton("log in", this); 
	m_qpToLogButton->setObjectName("toLog");
	m_qpToLogButton->setFixedHeight(TOLOG_H*yscale);
	m_qpToLogButton->setMinimumWidth(TOLOG_W*xscale);
}

void LogWindow::BuildConnections()
{
	connect(m_qpToLogButton, SIGNAL(clicked()), this, SLOT(change()));
	connect(m_qpCommitButton, SIGNAL(clicked()), this, SLOT(commit()));
}

void LogWindow::toLog()
{
	m_qlPwdcIcon->hide();
	m_qlePwdc->hide();
	m_qlEmailIcon->hide();
	m_qleEmail->hide();
	m_qlErrorMsg->hide();
	m_qpCommitButton->setText("Log in");
	m_qlToReg->setText("Do not have an account, click here to");
	m_qpToLogButton->setText("register");
	update();
}

void LogWindow::toReg()
{
	m_qlPwdcIcon->show();
	m_qlePwdc->show();
	m_qlEmailIcon->show();
	m_qleEmail->show();
	m_qlErrorMsg->hide();
	m_qpCommitButton->setText("Register");
	m_qlToReg->setText("If you already have an account, click here to");
	m_qpToLogButton->setText("log in");
	update();
}

void LogWindow::change()
{
	if (m_qpToLogButton->text() == "log in")
	{
		toLog();
	}
	else if (m_qpToLogButton->text() == "register")
	{
		toReg();
	}
}

void LogWindow::commit()
{
	
	QString userName = m_qleName->text();
	QString pwd = m_qlePwd->text();
	QString pwdc = m_qlePwdc->text();
	QString email = m_qleEmail->text();
	QString resultInfo;
	int result;
	if (m_qpCommitButton->text() == "Register")
	{
		result = g_umUserManager.Register(userName.toStdString(), pwd.toStdString(), pwdc.toStdString(), email.toStdString());
	}
	else if (m_qpCommitButton->text() == "Log in")
	{
		result = g_umUserManager.Login(userName.toStdString(), pwd.toStdString());
	}
	//result = SUCCESS;
	switch (result)
	{
	case SUCCESS:
		resultInfo = "Successfully";
		g_sPwd = pwd;
		if (m_qpCommitButton->text() == "Register")
		{
			g_umUserManager.SetUsername(userName.toStdString());
			emit regSuccess();
		}
		else
		{
			emit wait();
			emit logSuccess();
		}
		break;
	case USEREXIST:
		resultInfo = "User name already exsits!";
		break;
	case PWDNOTCON:
		resultInfo = "Two passwords are not consistent!";
		break;
	case PWDTOOSIM:
		resultInfo = "Password is too simple!";
		break;
	case EMAILFAIL:
		resultInfo = "Email address is not right!";
		break;
	case EMPTYINFO:
		if (userName == "")
		{
			resultInfo = "User name cannot be empty!";
		}
		else if (pwd == "")
		{
			resultInfo = "Password cannot be empty!";
		}
		else if (pwdc == "")
		{
			resultInfo = "Password confirm cannot be empty!";
		}
		else if (email == "")
		{
			resultInfo = "Email address cannot be empty!";
		}
		else
		{
			resultInfo = "Unknown empty!";
		}
		break;
	case LOGINFAIL:
		resultInfo = "Log in failed!";
		break;
	case ILEGALUSR:
		resultInfo = "Illegal character in the username!";
		break;
	default:
		resultInfo = "Unknown Error!";
		break;
	}
	m_qlErrorMsg->setText(resultInfo);
	m_qlErrorMsg->setWordWrap(true);
	m_qlErrorMsg->setAlignment(Qt::AlignCenter);
	m_qlErrorMsg->setObjectName("error");
	m_qlErrorMsg->setStyleSheet(QString("color: #FF7189;font-family:'Myriad Pro Light SemiExt';font-weight:bold;font-size:16pt;}"));
	m_qlErrorMsg->setMinimumWidth(800 * xscale);
	m_qlErrorMsg->show();
	//m_pFormLayout->insertWidget(8, qlErrorMsg);
	update();
}