#ifndef _UPLOADWINDOW_
#define _UPLOADWINDOW_

#include <MANAGER\UserManager.h>
#include "uploadwidget.h"
#include "posturewindow.h"
#include <QtWidgets\qmessagebox.h>

class UploadWindow : public PostureWindow
{
	Q_OBJECT
public:
	UploadWindow(QWidget*,QString);
	~UploadWindow();

protected:
	void BuildBottomRight();

private:
	UploadWidget *m_uwUpload;
	QPushButton *m_qpbStop;
	QPushButton *m_qpbCancel;
	QLabel *m_qlCardMsg;

	QMessageBox *m_qmbMsg;

	QString m_sHandMode;
	int m_iIsReal;
	int m_iIsPen;
	int m_iIsCard;

signals:
	void toUploadInfo(const QString&);

private slots:
	void upload();
	void msg(const QString&);
	void displayCardMsg(bool);
};

#endif//_UPLOADWINDOW_