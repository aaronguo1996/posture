#include "uploadmodewindow.h"

extern double xscale;
extern double yscale;

UploadModeWindow::UploadModeWindow(QWidget *parent)
	:PostureWindow(parent)
{
	m_iPicNo = 1;
	BuildBottomRight();
	m_qtTimer = new QTimer();
	m_qtTimer->start(2000);
	BuildConnections();
}

UploadModeWindow::~UploadModeWindow()
{

}

void UploadModeWindow::BuildBottomRight()
{
	m_qlFunc = new QLabel("Choose your own mode to upload", m_qwBottomRight);
	m_qlFunc->setObjectName("uploadTitle");
	m_qlFunc->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);

	m_qlLeftHand = new QLabel("Story Mode",m_qwBottomRight);
	m_qlLeftHand->setObjectName("upload");
	m_qlLeftHand->setFixedSize(UPLOAD_W*xscale, UPLOAD_H*yscale);

	m_qsLeftHand = new QSlider(m_qwBottomRight);
	m_qsLeftHand->setOrientation(Qt::Horizontal);
	m_qsLeftHand->setObjectName("upload");
	m_qsLeftHand->setFixedSize(110*xscale, 60*yscale);

	/*m_qlRightHand = new QLabel("Right Hand Mode", m_qwBottomRight);
	m_qlRightHand->setObjectName("upload");
	m_qlRightHand->setFixedSize(UPLOAD_W*xscale, UPLOAD_H*yscale);

	m_qsRightHand = new QSlider(m_qwBottomRight);
	m_qsRightHand->setOrientation(Qt::Horizontal);
	m_qsRightHand->setObjectName("upload");
	m_qsRightHand->setFixedSize(110*xscale, 60*yscale);*/

	m_qlCard = new QLabel("Card Mode", m_qwBottomRight);
	m_qlCard->setObjectName("upload");
	m_qlCard->setFixedSize(UPLOAD_W*xscale, UPLOAD_H*yscale);

	m_qsCard = new QSlider(m_qwBottomRight);
	m_qsCard->setOrientation(Qt::Horizontal);
	m_qsCard->setObjectName("upload");
	m_qsCard->setFixedSize(110*xscale, 60*yscale);

	/*m_qlPencil = new QLabel("Pencil Mode", m_qwBottomRight);
	m_qlPencil->setObjectName("upload");
	m_qlPencil->setFixedSize(UPLOAD_W*xscale, UPLOAD_H*yscale);
	
	m_qsPencil = new QSlider(m_qwBottomRight);
	m_qsPencil->setOrientation(Qt::Horizontal);
	m_qsPencil->setObjectName("upload");
	m_qsPencil->setFixedSize(110*xscale, 60*yscale);*/

	/*m_qlChooseModel = new QLabel("Choose Model", m_qwBottomRight);
	m_qlChooseModel->setObjectName("uploadTitle");
	m_qlChooseModel->setFixedSize(UPLOADTITLE_W*xscale, UPLOADTITLE_H*yscale);*/
	m_qpbLeft = new QPushButton("", m_qwBottomRight);
	m_qpbLeft->setObjectName("leftChoose");
	m_qpbRight = new QPushButton("", m_qwBottomRight);
	m_qpbRight->setObjectName("rightChoose");
	m_qlModel = new QLabel("Model", m_qwBottomRight);
	m_qlModel->setPixmap(QPixmap(g_sImgRoot + "1.jpg").scaled(PICWIDTH * 2 * xscale, PICHEIGHT * 2 * yscale));
	m_qlModel->setObjectName("model");
	m_qlModel->setFixedSize(PICWIDTH*2*xscale, PICHEIGHT*2*yscale);
	m_qlModel->setAlignment(Qt::AlignCenter);

	m_qpbBegin = new QPushButton("Begin", m_qwBottomRight);
	m_qpbBegin->setObjectName("detail");
	m_qpbBegin->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);
	m_qpbCancel = new QPushButton("Cancel", m_qwBottomRight);
	m_qpbCancel->setObjectName("detail");
	m_qpbCancel->setFixedSize(DETAIL_W*xscale, DETAIL_H*yscale);

	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->addStretch();

	QVBoxLayout *rightLayout = new QVBoxLayout();
	QHBoxLayout *leftHand = new QHBoxLayout();
	leftHand->addWidget(m_qlLeftHand);
	leftHand->addStretch();
	leftHand->addWidget(m_qsLeftHand);
	rightLayout->addLayout(leftHand);

	/*QHBoxLayout *rightHand = new QHBoxLayout();
	rightHand->addWidget(m_qlRightHand);
	rightHand->addStretch();
	rightHand->addWidget(m_qsRightHand);
	rightLayout->addLayout(rightHand);*/

	QHBoxLayout *card = new QHBoxLayout();
	card->addWidget(m_qlCard);
	card->addStretch();
	card->addWidget(m_qsCard);
	rightLayout->addLayout(card);

	/*QHBoxLayout *pencil = new QHBoxLayout();
	pencil->addWidget(m_qlPencil);
	pencil->addStretch();
	pencil->addWidget(m_qsPencil);
	rightLayout->addLayout(pencil);*/
	
	mainLayout->addLayout(rightLayout);
	mainLayout->addStretch();

	QVBoxLayout *buttonLayout = new QVBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_qpbBegin,0,Qt::AlignCenter);
	buttonLayout->addWidget(m_qpbCancel, 0, Qt::AlignCenter);
	buttonLayout->addStretch();

	mainLayout->addLayout(buttonLayout);
	mainLayout->addStretch();
	mainLayout->setMargin(0);

	QHBoxLayout *modelLayout = new QHBoxLayout();
	modelLayout->addWidget(m_qpbLeft);
	if (m_iPicNo == 0)m_qpbLeft->setDisabled(true);
	modelLayout->addWidget(m_qlModel);
	modelLayout->addWidget(m_qpbRight);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(m_qlFunc);
	layout->addLayout(mainLayout);
	//layout->addWidget(m_qlChooseModel);
	layout->addLayout(modelLayout);
	layout->addStretch();
	m_qwBottomRight->setLayout(layout);
}

void UploadModeWindow::BuildConnections()
{
	connect(m_qsLeftHand, SIGNAL(valueChanged(int)), this, SLOT(checkStoryValue(int)));
	connect(m_qsCard, SIGNAL(valueChanged(int)), this, SLOT(checkCardValue(int)));
	connect(m_qpbBegin, SIGNAL(clicked()), this, SLOT(record()));
	connect(m_qpbCancel, SIGNAL(clicked()), this, SIGNAL(toHome())); 
	connect(m_qpbLeft, SIGNAL(clicked()), this, SLOT(prevPic()));
	connect(m_qpbRight, SIGNAL(clicked()), this, SLOT(nextPic()));
	connect(m_qtTimer, SIGNAL(timeout()), this, SLOT(nextPic()));
}

void UploadModeWindow::checkCardValue(int value)
{
	if (m_qsCard->value() < m_qsCard->maximum() / 2)
	{
		m_qsCard->setValue(m_qsCard->minimum());
		m_qsCard->setObjectName("upload");
	}
	else if (m_qsCard->value() >= m_qsCard->maximum() / 2)
	{
		m_qsLeftHand->setValue(m_qsLeftHand->minimum());
		m_qsLeftHand->setObjectName("upload");
		m_qsCard->setValue(m_qsCard->maximum());
		m_qsCard->setObjectName("uploadRight");
	}
	
	this->setStyleSheet(
			QString("QSlider#upload::groove:horizontal\
					{\
					border:1px solid #999999;\
					border-radius:25px;\
					width:100px;\
					height:50px;\
					background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0#B1B1B1, stop:1 #c4c4c4);\
					}\
					QSlider#upload::handle:horizontal\
					{\
					background: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0#b4b4b4, stop:1 #8f8f8f);\
					border-radius:25px;\
					width:50px;\
					height:50px;\
					margin:-2px;\
					}"));
	this->setStyleSheet(
			QString("QSlider#uploadRight::groove:horizontal\
					{\
					border:1px solid #999999;\
					border-radius:25px;\
					width:100px;\
					height:50px;\
					background: #FF7189;\
					}\
					QSlider#uploadRight::handle:horizontal\
					{\
					background: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0#b4b4b4, stop:1 #8f8f8f);\
					border-radius:25px;\
					width:50px;\
					height:50px;\
					margin:-2px;\
					}"));
	update();
}
	/*if (m_qsRightHand->value() < m_qsRightHand->maximum() / 2)
	{
		m_qsRightHand->setValue(m_qsRightHand->minimum());
		m_qsRightHand->setObjectName("upload");
	}
	else if (m_qsRightHand->value() >= m_qsRightHand->maximum() / 2)
	{
		m_qsRightHand->setValue(m_qsRightHand->maximum());
		m_qsRightHand->setObjectName("uploadRight");
	}*/
void UploadModeWindow::checkStoryValue(int value)
{
	if (m_qsLeftHand->value() < m_qsLeftHand->maximum() / 2)
	{
		m_qsLeftHand->setValue(m_qsLeftHand->minimum());
		m_qsLeftHand->setObjectName("upload");
	}
	else if (m_qsLeftHand->value() >= m_qsLeftHand->maximum() / 2)
	{
		m_qsLeftHand->setValue(m_qsLeftHand->maximum());
		m_qsCard->setValue(m_qsCard->minimum());
		m_qsLeftHand->setObjectName("uploadRight");
		m_qsCard->setObjectName("upload");
	}
	
	this->setStyleSheet(
			QString("QSlider#upload::groove:horizontal\
					{\
					border:1px solid #999999;\
					border-radius:25px;\
					width:100px;\
					height:50px;\
					background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0#B1B1B1, stop:1 #c4c4c4);\
					}\
					QSlider#upload::handle:horizontal\
					{\
					background: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0#b4b4b4, stop:1 #8f8f8f);\
					border-radius:25px;\
					width:50px;\
					height:50px;\
					margin:-2px;\
					}"));
	this->setStyleSheet(
			QString("QSlider#uploadRight::groove:horizontal\
					{\
					border:1px solid #999999;\
					border-radius:25px;\
					width:100px;\
					height:50px;\
					background: #FF7189;\
					}\
					QSlider#uploadRight::handle:horizontal\
					{\
					background: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0#b4b4b4, stop:1 #8f8f8f);\
					border-radius:25px;\
					width:50px;\
					height:50px;\
					margin:-2px;\
					}"));
	update();
	
	/*if (m_qsPencil->value() < m_qsPencil->maximum() / 2)
	{
		m_qsPencil->setValue(m_qsPencil->minimum());
		m_qsPencil->setObjectName("upload");
	}
	else if (m_qsPencil->value() >= m_qsPencil->maximum() / 2)
	{
		m_qsPencil->setValue(m_qsPencil->maximum());
		m_qsPencil->setObjectName("uploadRight");
	}*/
	update();
}

void UploadModeWindow::record()
{
	if (m_qsLeftHand->value() / m_qsLeftHand->maximum())
	{
		emit toUpload(MODE_STORY);
	}
	else if (m_qsCard->value() / m_qsCard->maximum())
	{
		emit toUpload(MODE_CARD);
	}
	else
	{
		emit toUpload(MODE_REAL);
	}
}

void UploadModeWindow::prevPic()
{
	if (m_iPicNo == 1)
		m_iPicNo = 8;
	else
	{
		m_iPicNo--;
	}
	m_qlModel->setPixmap(QPixmap(QString(g_sImgRoot + "%1.jpg").arg(m_iPicNo)).scaled(PICWIDTH * 2 * xscale, PICHEIGHT * 2 * yscale));

	update();
}

void UploadModeWindow::nextPic()
{
	if (m_iPicNo == 8)
		m_iPicNo = 1;
	else
	{
		m_iPicNo++;
	}
	m_qlModel->setPixmap(QPixmap(QString(g_sImgRoot + "%1.jpg").arg(m_iPicNo)).scaled(PICWIDTH * 2 * xscale, PICHEIGHT * 2 * yscale));
	
	update();
}