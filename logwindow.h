#ifndef _LOGWINDOWH_
#define _LOGWINDOWH_

#include "MANAGER/UserManager.h"
#include <qobject.h>
#include <qmainwindow.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qboxlayout.h>
#include <QtGui\qpixmap.h>
#include <QtWidgets\qtooltip.h>
#include <QtCore\qdebug.h>
#include "globalDefs.h"

class LogWindow : public QWidget
{
	Q_OBJECT
public:
	LogWindow(QWidget*,int);
	~LogWindow();

private:
	QLabel *m_qlIcon;
	QLabel *m_qlNameIcon;
	QLabel *m_qlPwdIcon;
	QLabel *m_qlPwdcIcon;
	QLabel *m_qlEmailIcon;
	QLabel *m_qlErrorMsg;
	QLabel *m_qlToReg;

	QLineEdit *m_qleName;
	QLineEdit *m_qlePwd;
	QLineEdit *m_qlePwdc;
	QLineEdit *m_qleEmail;

	QPushButton *m_qpCommitButton;
	QPushButton *m_qpToLogButton;

	QToolTip *m_qttTip;

	void InitWidgets();
	void BuildConnections();

signals:
	void logSuccess();
	void regSuccess();
	void wait();
	
private slots:
	void change();
	void commit();
	void toLog();
	void toReg();
};

#endif//_LOGWINDOWH_