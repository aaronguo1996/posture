#include "posture.h"
#include <QtWidgets/qapplication.h>
#include <QtCore/qfile.h>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	Posture w;
	//LogWindow w;
	QString qss;
	QFile qssFile("stylesheet.css");
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
		qss = QLatin1String(qssFile.readAll());
		w.setStyleSheet(qss);
		qssFile.close();
	}

	w.show();
	return a.exec();
}
