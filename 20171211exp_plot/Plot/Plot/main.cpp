#include "Plot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Plot w;
	w.show();
	return a.exec();
}
