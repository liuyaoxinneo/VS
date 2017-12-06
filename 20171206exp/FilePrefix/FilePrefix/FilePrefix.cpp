#include "FilePrefix.h"
#include "qfile.h"
#include "qdebug.h"
#include "qtextstream.h"



FilePrefix::FilePrefix(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	unsigned char x[18755];
	for (int i = 0; i<18755; i++)
	{
		x[i] = i + 1;
	}
	QFile file("../../Data/out5.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	for (int p = 0; p<18755; p++)
	{
		out << x[p] << "\n";
	}
	file.close();
	qDebug() << "Data has been written";
}
