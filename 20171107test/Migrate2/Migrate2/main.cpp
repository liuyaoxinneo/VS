#include "Migrate2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Migrate2 w;
	w.show();
	return a.exec();
}
