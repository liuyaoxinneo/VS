#include "Migrate3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Migrate3 w;
	w.show();
	return a.exec();
}
