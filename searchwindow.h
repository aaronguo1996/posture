#ifndef _SEARCHWINDOW_
#define _SEARCHWINDOW_

#include "posturewindow.h"
#include "globalDefs.h"
#include <QtWidgets\qlineedit.h>

class SearchWindow : public PostureWindow
{
	Q_OBJECT
public:
	SearchWindow(QWidget*);
	~SearchWindow();

protected:
	void BuildBottomRight();

private:
	QLabel *m_qlNotify;
	
	QLineEdit *m_qleSearchKey;

	QPushButton *m_qpbSearch;
};

#endif//_SEARCHWINDOW_