#include "profileeditwindow.h"

extern UserManager g_umUserManager;
extern QString g_sPwd;
extern double xscale;
extern double yscale;

ProfileEditWindow::ProfileEditWindow(QWidget *parent)
	:PostureWindow(parent)
{
	InitWidgets();
	BuildBottomRight();
}

ProfileEditWindow::~ProfileEditWindow()
{

}

void ProfileEditWindow::InitWidgets()
{
	SourceManager sm;
	UserPro up;
	sm.GetUserProfile(up, g_umUserManager.GetUsername());
	m_qlName = new QLabel("Username", m_qwBottomRight);
	m_qlName->setObjectName("uploadInfo");
	m_qlName->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qleName = new QLineEdit(m_qwBottomRight);
	m_qleName->setObjectName("editProfile");
	m_qleName->setFixedSize(EDITPROFILE_W*xscale, EDITPROFILE_H*yscale);
	m_qleName->setText(up.m_sUserName.c_str());
	m_qleName->setReadOnly(true);

	m_qlPwd = new QLabel("Password", m_qwBottomRight);
	m_qlPwd->setObjectName("uploadInfo");
	m_qlPwd->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qlePwd = new QLineEdit(m_qwBottomRight);
	m_qlePwd->setEchoMode(QLineEdit::Password);
	m_qlePwd->setObjectName("editProfile");
	m_qlePwd->setFixedSize(EDITPROFILE_W*xscale, EDITPROFILE_H*yscale);

	m_qlPwdc = new QLabel("Password Confirm", m_qwBottomRight);
	m_qlPwdc->setObjectName("uploadInfo");
	m_qlPwdc->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qlePwdc = new QLineEdit(m_qwBottomRight);
	m_qlePwdc->setEchoMode(QLineEdit::Password);
	m_qlePwdc->setObjectName("editProfile");
	m_qlePwdc->setFixedSize(EDITPROFILE_W*xscale, EDITPROFILE_H*yscale);

	m_qlEmail = new QLabel("Email", m_qwBottomRight);
	m_qlEmail->setObjectName("uploadInfo");
	m_qlEmail->setFixedSize(UPLOADINFO_W*xscale, UPLOADINFO_H*yscale);
	m_qleEmail = new QLineEdit(m_qwBottomRight);
	m_qleEmail->setText(up.m_sEmail.c_str());
	m_qleEmail->setObjectName("editProfile");
	m_qleEmail->setFixedSize(EDITPROFILE_W*xscale, EDITPROFILE_H*yscale);

	m_qlError = new QLabel(m_qwBottomRight);

	m_qpbCancel = new QPushButton("Cancel", m_qwBottomRight);
	m_qpbCancel->setObjectName("detail");
	m_qpbCancel->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbSubmit = new QPushButton("Submit", m_qwBottomRight);
	m_qpbSubmit->setObjectName("detail");
	m_qpbSubmit->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(m_qpbSubmit, SIGNAL(clicked()), this, SLOT(submit()));
}

void ProfileEditWindow::BuildBottomRight()
{
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addWidget(m_qlName);
	nameLayout->addWidget(m_qleName);
	mainLayout->addLayout(nameLayout);

	QHBoxLayout *pwdLayout = new QHBoxLayout();
	pwdLayout->addWidget(m_qlPwd);
	pwdLayout->addWidget(m_qlePwd);
	mainLayout->addLayout(pwdLayout);

	QHBoxLayout *pwdcLayout = new QHBoxLayout();
	pwdcLayout->addWidget(m_qlPwdc);
	pwdcLayout->addWidget(m_qlePwdc);
	mainLayout->addLayout(pwdcLayout);

	QHBoxLayout *emailLayout = new QHBoxLayout();
	emailLayout->addWidget(m_qlEmail);
	emailLayout->addWidget(m_qleEmail);
	mainLayout->addLayout(emailLayout);

	mainLayout->addWidget(m_qlError,0,Qt::AlignCenter);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbSubmit);
	buttonLayout->addWidget(m_qpbCancel);
	buttonLayout->addStretch();
	mainLayout->addLayout(buttonLayout);

	m_qwBottomRight->setLayout(mainLayout);
}

void ProfileEditWindow::submit()
{
	string pwd = m_qlePwd->text().toStdString();
	string pwdc = m_qlePwdc->text().toStdString();
	if (pwd == "" && pwdc == "")
	{
		pwd = g_sPwd.toStdString();
		pwdc = g_sPwd.toStdString();
	}
	string email = m_qleEmail->text().toStdString();

	int result = g_umUserManager.ChangeProfile(pwd, pwdc, email);
	QString error;

	switch (result)
	{
	case SUCCESS:
		emit success("");
		return;
	case PWDNOTCON:
		error = "the password is not Consistent!";
		break;
	case PWDTOOSIM:
		error = "the password is too simple";
		break;
	case EMAILFAIL:
		error = "the email address is not right";
		break;
	case EMPTYINFO:
		error = "the information is empty";
		break;
	case PASSWORD2L:
		error = "the password is too long";
		break;
	}
	m_qlError->setText(error);
	m_qlError->setObjectName("error");
	m_qlError->setAlignment(Qt::AlignCenter);
	m_qlError->show();
}

void ProfileEditWindow::cancel()
{
	emit cancel("");
}