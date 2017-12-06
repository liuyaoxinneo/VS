#include "Plugin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Plugin w;
	w.show();
	return a.exec();
}
