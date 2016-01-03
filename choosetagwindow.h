#ifndef _CHOOSETAGWINDOW_
#define _CHOOSETAGWINDOW_

#include <MANAGER\UserManager.h>
#include "globalDefs.h"
#include "posturewindow.h"
#include <qobject.h>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qgridlayout.h>
#include <QtWidgets\qlayout.h>
#include <QtCore\qvariant.h>
#include <QtCore\qdebug.h>

class ChooseTagWindow : public PostureWindow
{
	Q_OBJECT
public:
	ChooseTagWindow(QWidget*);
	~ChooseTagWindow();

private:
	QLabel *m_qlTitle;
	QPushButton *m_qpbFavor;
	QPushButton *m_qpbSubmit;
	std::vector<QString> m_sFavor;
	std::vector<QString> m_sFavorRemove;

	int m_iFavor;
	void InitWidgets();

protected:
	void BuildBottomRight();

signals:
	void addSuccess(const QString&);

private slots:
	void choose();
	void done();
};

#endif//_CHOOSETAGWINDOW_