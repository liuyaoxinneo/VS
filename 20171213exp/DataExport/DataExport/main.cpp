#include "DataExport.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DataExport w;
	w.show();
	return a.exec();
}
