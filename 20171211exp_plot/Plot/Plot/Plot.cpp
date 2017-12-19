#include "Plot.h"
#include "ui_Plot.h"
#include "qfile.h"
#include "qdebug.h"
#include "qtextstream.h"

QString filename1;//data*.txt
QString filename2;//time*.txt
double inputdata[10][245];//存放10个角度的强度值
double inputtime[10][245];//存放10个角度的时间

QCPColorMap *colorMap;
int nx = 500, ny = 500;//显示区域的像素数量：500*500

int v = 5900;//材料中的声速，但是画图时如果用5900则坐标太大超出画图范围，换用a
int a = 20;

Plot::Plot(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initialization();

	dataimport();

	plot();

}

void Plot::initialization()
{
	ui.plot->axisRect()->setupFullAxesBox(true);
	ui.plot->xAxis->setTickLabels(false);
	ui.plot->xAxis2->setTickLabels(false);
	ui.plot->xAxis2->setLabel("x");
	ui.plot->yAxis->setTickLabels(false);
	ui.plot->yAxis->setLabel("y");
	ui.plot->yAxis2->setTickLabels(false);

	colorMap = new QCPColorMap(ui.plot->xAxis, ui.plot->yAxis);
	colorMap->data()->setSize(nx, ny); 

	//添加色彩的图示
	QCPColorScale *colorScale = new QCPColorScale(ui.plot);
	ui.plot->plotLayout()->addElement(0, 1, colorScale);
	colorScale->setDataRange(QCPRange(0, 2));//设置数值的范围
	colorMap->setColorScale(colorScale);

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
	colorMap->setGradient(neo);

	QCPMarginGroup *marginGroup = new QCPMarginGroup(ui.plot);
	ui.plot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

	//显示区域的交互：鼠标的拖拽，滚轮放大缩小
	ui.plot->rescaleAxes();
	ui.plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
}

void Plot::dataimport()
{
	qDebug() << "begin import data:";
	for (int number = 6; number < 26; number = number + 2)
	{
		filename1 = QString("../../Data/data%1.txt")
			.arg(number);
		filename2= QString("../../Data/time%1.txt")
			.arg(number);

		int index = 0.5*(number - 6);

		QFile file(filename1);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "can't open" << filename1 << endl;
		}
		else
		{
			QString str2;
			while (!file.atEnd())
			{
				for (int j = 0; j < 245; j++)
				{
					QByteArray line = file.readLine();
					QString str(line);
					str2 = str.left((str.length() - 1));
					double buf1 = str2.toDouble();
					inputdata[index][j] = abs(buf1);//对负的幅值先取绝对值
				}
			}
		}

		QFile file2(filename2);
		if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "can't open" << filename2 << endl;
		}
		else
		{
			QString str2;
			while (!file2.atEnd())
			{
				for (int j = 0; j < 245; j++)
				{
					QByteArray line = file2.readLine();
					QString str(line);
					str2 = str.left((str.length() - 1));
					double buf2 = str2.toDouble();
					inputtime[index][j] = buf2;
				}
			}
		}

		//for (int i = 0; i < 245; i++)
		//{
		//	qDebug() << inputdata[1][i];
		//}
	}
	qDebug() << "finished!";
}

void Plot::plot()
{
	//先进行坐标分配
	for (int index2 = 0; index2 < 10; index2++)
	{
		int angle;
		double xindex, yindex;
		double t, buf;
		for (int n = 0; n < 245; n++)
		{
			angle = 2 + 2 * index2;
			//t = inputtime[index2][n]- inputtime[index2][0];
			t = inputtime[index2][n];
			xindex = ceil(a*t*cos(angle*M_PI / 180));
			yindex = ceil(a*t*sin(angle*M_PI / 180));
			buf = inputdata[index2][n];
			colorMap->data()->setCell(xindex, yindex, buf);//分配强度值点的坐标
		}
	}
}