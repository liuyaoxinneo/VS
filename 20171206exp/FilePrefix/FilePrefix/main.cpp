#include "FilePrefix.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FilePrefix w;
	w.show();
	return a.exec();
}
