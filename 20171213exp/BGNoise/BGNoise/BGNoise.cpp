#include "BGNoise.h"
#include "qfile.h"
#include "qdebug.h"

QString noisename;
QString dataname;
int noise[18755];
int input[18755];
int output[18755];

BGNoise::BGNoise(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	dataimport();

	nc();

	//for (int i = 0; i < 18755; i++)
	//{
	//	qDebug() << input[i];
	//}
}

void BGNoise::dataimport()
{
	noisename = QString("../../Data/background.txt");
	dataname = QString("../../Data/52.txt");

	QFile file(noisename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "can't open" << noisename << endl;
	}
	else
	{
		QString str1;
		while (!file.atEnd())
		{
			for (int j = 0; j < 18755; j++)
			{
				QByteArray line = file.readLine();
				QString str(line);
				str1 = str.left((str.length() - 1));
				int buf1 = str1.toInt();
				noise[j] = buf1;
			}
		}
	}

	QFile file2(dataname);
	if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "can't open" << dataname << endl;
	}
	else
	{
		QString str2;
		while (!file2.atEnd())
		{
			for (int j = 0; j < 18755; j++)
			{
				QByteArray line2 = file2.readLine();
				QString str(line2);
				str2 = str.left((str.length() - 1));
				int buf2 = str2.toInt();
				input[j] = buf2;
			}
		}
	}

}

void BGNoise::nc()
{

}