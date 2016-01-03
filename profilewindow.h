#ifndef _PROFILEWINDOW_
#define _PROFILEWINDOW_

#include "MANAGER\UserManager.h"
#include "MANAGER\SourceManager.h"
#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qmessagebox.h>

class ProfileWindow : public PostureWindow
{
	Q_OBJECT
public:
	ProfileWindow(QWidget*,QString);
	~ProfileWindow();

protected:
	void BuildBottomRight();

private:
	QLabel *m_qlImg;
	QLabel *m_qlNameImg;
	QLabel *m_qlNameTitle;
	QLabel *m_qlName;
	QLabel *m_qlEmailImg;
	QLabel *m_qlEmailTitle;
	QLabel *m_qlEmail;
	QLabel *m_qlTags;

	QPushButton *m_qpbEdit;
	QPushButton *m_qpbReturn;
	QPushButton *m_qpbTag;
	QPushButton *m_qpbAddTag;

	QString m_sUsername;

	QMessageBox *m_qmbMsg;

	void InitWidgets();
	void IsFollowed();

signals:
	void edit();
	void addTag();

private slots:
	void follow();
	void unfollow(QAbstractButton*);
	void toProfile();
	void message();
};

#endif//_PROFILEWINDOW_