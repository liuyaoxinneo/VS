#include "BGNoise.h"
#include "qfile.h"
#include "qdebug.h"

QString noisename;
QString dataname;
int noise[18755];
int input[18755];
int output[18755];

QCPColorMap *map1;
QCPColorMap *map2;
int a = 800;//a=800/1000是比较合适的值
int nx = 700, ny = 700;
int mapbuf1[700][700];
int mapbuf2[700][700];
int tag0 = 1, tag1 = 2, tag2 = 3, tag3 = 4;
int xindex, yindex, angle, buf, radius = 6;


BGNoise::BGNoise(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initial();

	dataimport();

	nc();

	plot1();
	plot2();
}

void BGNoise::initial()
{
	ui.label1->setText("input");
	ui.label2->setText("output");

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

	map1 = new QCPColorMap(ui.plot1->xAxis, ui.plot1->yAxis);
	map1->data()->setSize(nx, ny);
	map2 = new QCPColorMap(ui.plot2->xAxis, ui.plot2->yAxis);
	map2->data()->setSize(nx, ny);

	//添加色彩的图示
	QCPColorScale *colorScale = new QCPColorScale(ui.plot1);
	colorScale->setDataRange(QCPRange(0, 255));//设置数值的范围
	map1->setColorScale(colorScale);
	map2->setColorScale(colorScale);

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

	map1->setGradient(neo);
	map2->setGradient(neo);

	QCPMarginGroup *marginGroup1 = new QCPMarginGroup(ui.plot1);
	ui.plot1->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup1);
	QCPMarginGroup *marginGroup2 = new QCPMarginGroup(ui.plot2);
	ui.plot2->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup2);
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
		qDebug() << output[n];
	}
}

void BGNoise::plot1()
{
	//1初始化
	double x1, y1;
	for (int x1Index = 0; x1Index<nx; ++x1Index)
	{
		for (int y1Index = 0; y1Index<ny; ++y1Index)
		{
			map1->data()->cellToCoord(x1Index, y1Index, &x1, &y1);
			if (((3 * ny - 3 * y1Index) >= (x1Index*sqrt(3))) && ((y1Index - ny) >= (-x1Index*sqrt(3))) && (pow(x1Index, 2.0) + pow(y1Index - ny, 2.0) <= pow(a + 3, 2.0)))//a+3的原因：使弧边更圆润
			{
				map1->data()->setCell(x1Index, y1Index, 0);
				mapbuf1[x1Index][y1Index] = tag0;//map2中扇形区域内的点被初始化为tag0
			}
			else
			{
				map1->data()->setCell(x1Index, y1Index, 300);
				mapbuf1[x1Index][y1Index] = 0;
			}
		}
	}
	//2为有对应坐标的离散点赋强度值
	for (int p = 0; p<31; p++)
	{
		angle = p + 30;
		for (int q = 0; q<605; q++)
		{
			xindex = ceil(q*a*cos(angle*M_PI / 180) / 604);
			yindex = ceil(q*a*sin(angle*M_PI / 180) / 604);
			buf = input[p * 605 + q];
			//重复赋值的处理：对单个像素点重复赋值时，取最大的值作为最后的值
			if (mapbuf1[yindex][ny - 1 - xindex] == tag0)//若这个点以前没被赋过值
			{
				map1->data()->setCell(yindex, ny - 1 - xindex, buf);
				mapbuf1[yindex][ny - 1 - xindex] = tag1;
			}
			else
			{
				if ((map1->data()->cell(yindex, ny - 1 - xindex))<buf)
					map1->data()->setCell(yindex, ny - 1 - xindex, buf);
			}
		}
	}

	//3插值
	double xinsert, yinsert, val = 0;
	int count = 1, step1, step2;
	double beta = 2.0;
	double di, d0 = 0, vi, wi, w0 = 0;
	for (int xIndex = 0; xIndex<nx; xIndex++)
	{
		for (int yIndex = 0; yIndex<ny; yIndex++)
		{
			map1->data()->cellToCoord(xIndex, yIndex, &xinsert, &yinsert);

			if ((mapbuf1[xIndex][yIndex] == tag0))//若是扇形区域内的点但是还没有插值的话
			{
				for (int n = 1; n<radius + 1; n++)
				{
					for (step1 = -n; step1<n + 1; step1++)
					{
						for (step2 = -n; step2<n + 1; step2++)
						{
							if ((mapbuf1[xIndex + step1][yIndex + step2] == tag1))
							{
								di = 1 / pow((pow(step1, 2) + pow(step2, 2)), 0.5*beta);
								d0 = d0 + di;
								vi = map1->data()->cell(xIndex + step1, yIndex + step2);
								wi = vi*di;
								w0 = w0 + wi;
								count++;
							}
						}
					}
				}

				for (int i = 0; i<count; ++i)
				{
					val = w0 / d0;
				}
				map1->data()->setCell(xIndex, yIndex, val);

				count = 1;
				val = 0;
				d0 = 0;
				w0 = 0;
			}
		}
	}

}

void BGNoise::plot2()
{
	//1初始化
	double x1, y1;
	for (int x1Index = 0; x1Index<nx; ++x1Index)
	{
		for (int y1Index = 0; y1Index<ny; ++y1Index)
		{
			map2->data()->cellToCoord(x1Index, y1Index, &x1, &y1);
			if (((3 * ny - 3 * y1Index) >= (x1Index*sqrt(3))) && ((y1Index - ny) >= (-x1Index*sqrt(3))) && (pow(x1Index, 2.0) + pow(y1Index - ny, 2.0) <= pow(a + 3, 2.0)))//a+3的原因：使弧边更圆润
			{
				map2->data()->setCell(x1Index, y1Index, 0);
				mapbuf2[x1Index][y1Index] = tag0;//map2中扇形区域内的点被初始化为tag0
			}
			else
			{
				map2->data()->setCell(x1Index, y1Index, 300);
				mapbuf2[x1Index][y1Index] = 0;
			}
		}
	}
	//2为有对应坐标的离散点赋强度值
	for (int p = 0; p<31; p++)
	{
		angle = p + 30;
		for (int q = 0; q<605; q++)
		{
			xindex = ceil(q*a*cos(angle*M_PI / 180) / 604);
			yindex = ceil(q*a*sin(angle*M_PI / 180) / 604);
			buf = output[p * 605 + q];
			//重复赋值的处理：对单个像素点重复赋值时，取最大的值作为最后的值
			if (mapbuf2[yindex][ny - 1 - xindex] == tag0)//若这个点以前没被赋过值
			{
				map2->data()->setCell(yindex, ny - 1 - xindex, buf);
				mapbuf2[yindex][ny - 1 - xindex] = tag1;
			}
			else
			{
				if ((map2->data()->cell(yindex, ny - 1 - xindex))<buf)
					map2->data()->setCell(yindex, ny - 1 - xindex, buf);
			}
		}
	}

	//3插值
	double xinsert, yinsert, val = 0;
	int count = 1, step1, step2;
	double beta = 2.0;
	double di, d0 = 0, vi, wi, w0 = 0;
	for (int xIndex = 0; xIndex<nx; xIndex++)
	{
		for (int yIndex = 0; yIndex<ny; yIndex++)
		{
			map2->data()->cellToCoord(xIndex, yIndex, &xinsert, &yinsert);

			if ((mapbuf2[xIndex][yIndex] == tag0))//若是扇形区域内的点但是还没有插值的话
			{
				for (int n = 1; n<radius + 1; n++)
				{
					for (step1 = -n; step1<n + 1; step1++)
					{
						for (step2 = -n; step2<n + 1; step2++)
						{
							if ((mapbuf2[xIndex + step1][yIndex + step2] == tag1))
							{
								di = 1 / pow((pow(step1, 2) + pow(step2, 2)), 0.5*beta);
								d0 = d0 + di;
								vi = map1->data()->cell(xIndex + step1, yIndex + step2);
								wi = vi*di;
								w0 = w0 + wi;
								count++;
							}
						}
					}
				}

				for (int i = 0; i<count; ++i)
				{
					val = w0 / d0;
				}
				map2->data()->setCell(xIndex, yIndex, val);

				count = 1;
				val = 0;
				d0 = 0;
				w0 = 0;
			}
		}
	}

}