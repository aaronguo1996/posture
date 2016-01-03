#ifndef _PROFILEEDITWINDOW_
#define _PROFILEEDITWINDOW_

#include "MANAGER\SourceManager.h"
#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qlineedit.h>

class ProfileEditWindow : public PostureWindow
{
	Q_OBJECT
public:
	ProfileEditWindow(QWidget*);
	~ProfileEditWindow();

protected:
	void BuildBottomRight();

private:
	QLabel *m_qlTitle;
	QLabel *m_qlName;
	QLabel *m_qlPwd;
	QLabel *m_qlPwdc;
	QLabel *m_qlEmail;
	QLabel *m_qlError;

	QLineEdit *m_qleName;
	QLineEdit *m_qlePwd;
	QLineEdit *m_qlePwdc;
	QLineEdit *m_qleEmail;

	QPushButton *m_qpbSubmit;
	QPushButton *m_qpbCancel;

	void InitWidgets();

private slots:
	void submit();

signals:
	void cancel(const QString&);
	void success(const QString&);

private slots:
	void cancel();
};

#endif//_PROFILEEDITWINDOW_