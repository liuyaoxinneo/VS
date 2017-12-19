#include "BGNoise.h"
#include "qfile.h"
#include "qdebug.h"
#include "qcustomplot.h"

QString noisename;
QString dataname;
int noise[18755];
int input[18755];
int output[18755];

QCPColorMap *colorMap1;
QCPColorMap *colorMap2;
int nx = 700, ny = 700;//显示区域的像素数量：700*700

int map[700][700];
int a = 800;
int angle, yindex, xindex, buf;
int radius = 5;

BGNoise::BGNoise(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	dataimport();

	nc();

	plot();
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
	for (int n = 0; n < 18755; n++)
	{
		output[n] = input[n] - noise[n];
	}

}

void BGNoise::initialization()
{
	ui.label1->setText("Input");
	ui.label2->setText("Output");

	ui.plot1->axisRect()->setupFullAxesBox(true);
	ui.plot1->xAxis->setTickLabels(false);
	ui.plot1->xAxis2->setTickLabels(false);
	ui.plot1->xAxis2->setLabel("x");
	ui.plot1->yAxis->setTickLabels(false);
	ui.plot1->yAxis->setLabel("y");
	ui.plot1->yAxis2->setTickLabels(false);

	ui.plot2->axisRect()->setupFullAxesBox(true);
	ui.plot2->xAxis->setTickLabels(false);
	ui.plot2->xAxis2->setTickLabels(false);
	ui.plot2->xAxis2->setLabel("x");
	ui.plot2->yAxis->setTickLabels(false);
	ui.plot2->yAxis->setLabel("y");
	ui.plot2->yAxis2->setTickLabels(false);

	colorMap1 = new QCPColorMap(ui.plot1->xAxis, ui.plot1->yAxis);
	colorMap1->data()->setSize(nx, ny);
	colorMap2 = new QCPColorMap(ui.plot2->xAxis, ui.plot2->yAxis);
	colorMap2->data()->setSize(nx, ny);

	//添加色彩的图示
	QCPColorScale *colorScale = new QCPColorScale(ui.plot1);
	ui.plot1->plotLayout()->addElement(0, 1, colorScale);
	colorScale->setDataRange(QCPRange(0, 255));//设置数值的范围
	colorMap1->setColorScale(colorScale);

	//设置色彩梯度
	QCPColorGradient neo;
	neo.setLevelCount(350);
	neo.setColorStopAt(0, Qt::white);
	neo.setColorStopAt(0.3, QColor(0, 26, 123, 255));
	neo.setColorStopAt(0.4, QColor(56, 142, 113, 255));
	neo.setColorStopAt(0.5, QColor(162, 204, 58, 255));
	neo.setColorStopAt(0.57, Qt::yellow);
	neo.setColorStopAt(0.6, QColor(239, 210, 31, 255));
	neo.setColorStopAt(0.7, QColor(208, 126, 89, 255));
	neo.setColorStopAt(0.8, QColor(203, 114, 48, 255));
	neo.setColorStopAt(0.9, QColor(177, 73, 18, 255));
	neo.setColorStopAt(0.95, QColor(162, 40, 19, 255));
	neo.setColorStopAt(1, Qt::black);
	neo.setColorInterpolation(neo.ciRGB);

	colorMap1->setGradient(neo);
	colorMap2->setGradient(neo);
}

void BGNoise::plot()
{
	for (int p = 0; p < 31; p++)
	{
		int angle = p + 30;
		for (int q = 0; q < 605; q++)
		{
			xindex = ceil(q*a*cos(angle*M_PI / 180) / 604);
			yindex = ceil(q*a*sin(angle*M_PI / 180) / 604);
			buf = input[p * 605 + q];

			colorMap1->data()->setCell(yindex, ny-1-xindex, buf);
		}
	}
}