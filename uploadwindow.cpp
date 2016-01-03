#include "uploadwindow.h"

extern double xscale;
extern double yscale;

UploadWindow::UploadWindow(QWidget *parent, QString mode)
	:PostureWindow(parent), m_sHandMode(mode)
{
	BuildBottomRight();
	CloseFuncs();
}

UploadWindow::~UploadWindow()
{

}

void UploadWindow::BuildBottomRight()
{
	switch (m_sHandMode.toInt())
	{
	case 0: case 2:default:
		m_uwUpload = new UploadWidget(m_qwBottomRight, TWO_HANDS);
		break;
	case 1:
		m_uwUpload = new UploadWidget(m_qwBottomRight, TWO_HANDS_OBJECT);
		break;
	}
	m_uwUpload->setObjectName("upload");
	m_uwUpload->setFixedSize(UPLOADWIDGET_W*xscale, UPLOADWIDGET_H*yscale);
	
	if (m_sHandMode == "1")
	{
		m_qlCardMsg = new QLabel("Is card captured: false", m_qwBottomRight);
		m_qlCardMsg->setStyleSheet(QString("color: #FF7189;font-family:'Myriad Pro Light SemiExt';font-weight:bold;font-size:16pt;}"));
		m_qlCardMsg->setMinimumWidth(800 * xscale);
		connect(m_uwUpload, SIGNAL(cardMsg(bool)), this, SLOT(displayCardMsg(bool)));
	}

	m_qpbStop = new QPushButton("Stop", m_qwBottomRight);
	m_qpbStop->setObjectName("detail");
	m_qpbStop->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbCancel = new QPushButton("Cancel", m_qwBottomRight);
	m_qpbCancel->setObjectName("detail");
	m_qpbCancel->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	connect(m_qpbStop, SIGNAL(clicked()), m_uwUpload, SLOT(stop()));
	connect(m_qpbStop, SIGNAL(clicked()), this, SLOT(upload()));
	connect(m_qpbCancel, SIGNAL(clicked()), m_uwUpload, SLOT(stop()));
	connect(m_qpbCancel, SIGNAL(clicked()), this, SIGNAL(toUpload()));
	connect(m_uwUpload, SIGNAL(msg(const QString&)), this, SLOT(msg(const QString&)));
	
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addStretch();
	mainLayout->addWidget(m_uwUpload, 0, Qt::AlignCenter);
	if (m_sHandMode == "1")
		mainLayout->addWidget(m_qlCardMsg, 0, Qt::AlignCenter);
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbStop);
	buttonLayout->addWidget(m_qpbCancel);
	buttonLayout->addStretch();
	mainLayout->addLayout(buttonLayout);
	mainLayout->addStretch();

	m_qwBottomRight->setLayout(mainLayout);
}

void UploadWindow::upload()
{
	emit toUploadInfo(m_sHandMode);
}

void UploadWindow::msg(const QString &message)
{
	m_uwUpload->close();
	m_qmbMsg = new QMessageBox(this);
	m_qmbMsg->setText(message);
	m_qmbMsg->setWindowModality(Qt::WindowModal);
	m_qmbMsg->show();
	connect(m_qmbMsg, SIGNAL(buttonClicked(QAbstractButton*)), this, SIGNAL(toUpload()));
}

void UploadWindow::displayCardMsg(bool isCardCaptured)
{
	m_qlCardMsg->setText(QString("Is card captured: %1").arg(isCardCaptured));
	update();
}