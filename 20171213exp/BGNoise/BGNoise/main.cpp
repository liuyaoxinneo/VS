#include "BGNoise.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BGNoise w;
	w.show();
	return a.exec();
}
