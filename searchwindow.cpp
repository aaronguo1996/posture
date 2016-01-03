#include "searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent)
	:PostureWindow(parent)
{
	BuildBottomRight();
}

SearchWindow::~SearchWindow()
{

}

void SearchWindow::BuildBottomRight()
{
	m_qlNotify = new QLabel("Search key words that you are interested in...",m_qwBottomRight);
	m_qlNotify->setObjectName("search");

	m_qleSearchKey = new QLineEdit(m_qwBottomRight);
	m_qleSearchKey->setPlaceholderText("for example: magic");
	m_qleSearchKey->setObjectName("searchKey");

	m_qpbSearch = new QPushButton(m_qwBottomRight);
	m_qpbSearch->setIcon(QIcon(":/img/Resources/searchbutton.png"));
	m_qpbSearch->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
	m_qpbSearch->setObjectName("search");

	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *searchLayout = new QHBoxLayout();
	searchLayout->addStretch();
	searchLayout->addWidget(m_qleSearchKey);
	searchLayout->addWidget(m_qpbSearch);
	searchLayout->addStretch();
	searchLayout->setSpacing(0);

	mainLayout->addSpacing(SPACE*10);
	mainLayout->addWidget(m_qlNotify, 0, Qt::AlignCenter);
	mainLayout->addSpacing(SPACE);
	mainLayout->addLayout(searchLayout);
	mainLayout->addStretch();
	m_qwBottomRight->setLayout(mainLayout);
}