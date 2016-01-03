#ifndef _UPLOADINFOWINDOW_
#define _UPLOADINFOWINDOW_

#include <MANAGER\UserManager.h>
#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qtextedit.h>
#include <QtWidgets\qlineedit.h>
#include <ctime>
#include <QtWidgets\qmessagebox.h>

class UploadInfoWindow : public PostureWindow
{
	Q_OBJECT
public:
	UploadInfoWindow(QWidget *,QString);
	~UploadInfoWindow();

protected:
	void BuildBottomRight();

private:
	QLabel *m_qlTitle;
	QLabel *m_qlOutline;
	QLabel *m_qlDesc;
	QLabel *m_qlTags;
	QLabel *m_qlNotify;

	QLineEdit *m_qleOutline;

	QTextEdit *m_qteDesc;

	QWidget *m_qwTagChoosed;
	QWidget *m_qwTagToChoose;
	QGridLayout *m_qglTagChoosed;
	QGridLayout *m_qglTagToChoose;

	QPushButton *m_qpbDance;
	QPushButton *m_qpbMagic;
	QPushButton *m_qpbCard;
	QPushButton *m_qpbPencil;
	QPushButton *m_qpbStory;
	QPushButton *m_qpbFairy;
	QPushButton *m_qpbGame;
	QPushButton *m_qpbMartial;
	QPushButton *m_qpbSubmit;
	QPushButton *m_qpbCancel;
	QPushButton *m_qpbChoose;

	QString m_sHandMode;
	int m_iIsReal;
	int m_iIsPen;
	int m_iIsCard;
	void InitWidgets();

signals:
	void toHomeWin();

private slots:
	void submit();
	void addTag();
	void removeTag();
};


#endif//_UPLOADINFOWINDOW_