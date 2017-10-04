#include "mainwindow.h"
#include"ui_mainwindow.h"
#include<QDebug>
#include<QTime>


//����ȫ�ֱ���
unsigned char map2[700][700];
unsigned char input[18755];
int tag0 = 1, tag1 = 2, tag2 = 3, tag3 = 4;
//tag0�����������ڵĵ�
//tag1�����������ڳ�ʼǿ��ֵ��Ӧ�ĵ�
//tag2�����������ڲ�ֵ�õ��ĵ�
//tag3����ʾ��ֵ�õ��ĵ��پ���һ��ƽ������
int anglecount;
int a = 800;//a=800/1000�ǱȽϺ��ʵ�ֵ
int nx = 700;
int ny = 700;//ny,nx���������ֵ=a*sqrt(3)/2
int radius = 5;//IDWѰ�ҷ���İ뾶
int yindex, xindex;
double angle;
unsigned char buf;
int number = 0;
int flag;//�ж���û�ж�Ӧ��data�ļ�
QString dataname;
QCPColorMap *colorMap;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//�������ļ�
	dataimport();

	//��������
	setWindowTitle("PHASCAN�������");//���ڼӱ���

	//��ͼ�ĳ�ʼ��
	//��ʼ��
	initialization();

	//����Ϊ��ͼ����
	//aɨ��ͼ������qCustomPlot2��
	ascan();

	//sɨ��ͼ������qCustomPlot��
	sscan();

	//����������
	//״̬����ʾ��ǰʱ��
	QTimer*timer1 = new QTimer(this);
	connect(timer1, SIGNAL(timeout()), this, SLOT(timeupdate()));
	timer1->start(1000);//ÿ��1�뷢��һ��timeout�ź�

	connect(ui.angle_spinBox, SIGNAL(valueChanged(int)), this, SLOT(ascan()));//���Ƕ�ѡ������ֵ�仯

	connect(ui.materialbox, SIGNAL(currentIndexChanged(int)), this, SLOT(material()));

	connect(ui.data_spinBox, SIGNAL(valueChanged(int)), this, SLOT(dataimport()));
	connect(ui.data_spinBox, SIGNAL(valueChanged(int)), this, SLOT(ascan()));//��ͬ�������ļ�������ʾ��ͬ��Aɨ��Sɨ
	connect(ui.data_spinBox, SIGNAL(valueChanged(int)), this, SLOT(sscan()));


}

void MainWindow::dataimport()
{

	number = ui.data_spinBox->value();
	dataname = QString("data%1.txt")
		.arg(number);

	QFile file(dataname);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "can't open " << dataname << endl;
		{
			for (int m = 0; m<18755; m++)
				input[m] = 0;
		};
		flag = 0;
	}

	else
	{
		flag = 1;
		//readLine����
		QString str2;
		while (!file.atEnd())
		{
			qDebug() << "begin import:" << dataname;
			for (int j = 0; j<18755; j++)
			{
				QByteArray line = file.readLine();
				QString str(line);
				str2 = str.left((str.length() - 1));
				int buf2 = str2.toInt();
				input[j] = (unsigned char)buf2;
			}
		}
		qDebug() << dataname << "imported!";
	}
}

void MainWindow::initialization()
{
	//aɨ�ĳ�ʼ��
	ui.qCustomPlot2->addGraph();//��qcustomplot�������һ������
	ui.qCustomPlot2->graph(0)->setPen(QPen(QColor(0, 0, 125, 255)));//����aɨ����ɫΪ����
	ui.qCustomPlot2->graph(0)->setLineStyle(QCPGraph::LineStyle::lsStepCenter);//���û�������
																				// �����ᣬ�����ϵı�ǩ�Ƿ�ɼ�
	ui.qCustomPlot2->xAxis->setVisible(true);
	ui.qCustomPlot2->xAxis2->setVisible(false);
	ui.qCustomPlot2->yAxis->setVisible(true);
	ui.qCustomPlot2->yAxis2->setVisible(false);

	ui.qCustomPlot2->xAxis->setTickLabels(true);
	ui.qCustomPlot2->xAxis2->setTickLabels(false);
	ui.qCustomPlot2->yAxis->setTickLabels(true);
	ui.qCustomPlot2->yAxis2->setTickLabels(false);

	ui.qCustomPlot2->xAxis->setRange(0, 80);
	ui.qCustomPlot2->yAxis->setRange(0, 100);//����y,x�ķ�Χ
	ui.qCustomPlot2->xAxis->setLabel("���(mm)");
	ui.qCustomPlot2->yAxis->setLabel("ǿ��(%)");

	//sɨ�ĳ�ʼ��-----------------------
	ui.qCustomPlot->axisRect()->setupFullAxesBox(true);//ʹ4���������ʾ
	ui.qCustomPlot->xAxis->setTickLabels(false);
	ui.qCustomPlot->xAxis2->setTickLabels(false);
	ui.qCustomPlot->xAxis2->setLabel("����(mm)");
	ui.qCustomPlot->yAxis->setTickLabels(false);
	ui.qCustomPlot->yAxis->setLabel("���(mm)");
	ui.qCustomPlot->yAxis2->setTickLabels(false);

	colorMap = new QCPColorMap(ui.qCustomPlot->xAxis, ui.qCustomPlot->yAxis);
	colorMap->data()->setSize(nx, ny); //ʹ��һ����nx * ny�����ݵ�

									   //���ɫ�ʵ�ͼʾ
	QCPColorScale *colorScale = new QCPColorScale(ui.qCustomPlot);
	ui.qCustomPlot->plotLayout()->addElement(0, 1, colorScale);
	colorScale->setDataRange(QCPRange(0, 300));
	colorMap->setColorScale(colorScale);

	//���³����Լ�����ɫ���ݶ�
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

	QCPMarginGroup *marginGroup = new QCPMarginGroup(ui.qCustomPlot);
	ui.qCustomPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
	//-----------------------

	//ѡ�����ݳ�ʼ��
	ui.data_spinBox->setRange(0, 2000);
	ui.data_spinBox->setSingleStep(1);

	//ui��ʼ����һ����
	//ѡ����ʾ�Ƕ�
	ui.label1->setText("�Ƕ�");
	ui.angle_spinBox->setRange(30, 60);
	ui.angle_spinBox->setSingleStep(1);

	//ѡ������
	ui.gainnumber->setRange(0.0, 100.0);
	ui.gainnumber->setValue((net.gain())*0.1);//��ȡĿǰ���������ã���Ϊ�����ĳ�ֵ
	ui.gainnumber->setSingleStep(1);
	ui.gainlabel->setText("����");

	//ѡ��������ͣ�ȷ������
	ui.vol->display(3000);
	ui.materials->setText("��ǰ����");


}

void MainWindow::ascan()
{
	//���ɣ����ͳ�ʼ����
	QVector<double> x(605), y(605);
	QVector<double> n(605), m(605);
	anglecount = ui.angle_spinBox->value();
	for (int i = 0; i<605; i++)
	{
		x[i] = i + 0.0;//+0.0ʹ���Ϊdouble�ͣ������*1.0Ҳ��ͬ��
		y[i] = 1.0*input[605 * (anglecount - 30) + i];
		//���¸Ľ�Aɨ�ĺ������꣬ʹ֮������һ��
		n[i] = 0.153*i*cos(M_PI*anglecount / 180);
		m[i] = y[i] * 20 / 51;
	}
	ui.qCustomPlot2->graph(0)->setData(n, m);//Ϊ�����ߣ�����Ϊgraph0����������
	ui.qCustomPlot2->replot();//�ػ棬�����ڶ�̬ͼ
	anglecount = ui.angle_spinBox->value();
}

void MainWindow::sscan()
{
	//��ʼ��
	double x1, y1;
	for (int x1Index = 0; x1Index<nx; ++x1Index)
	{
		for (int y1Index = 0; y1Index<ny; ++y1Index)
		{
			colorMap->data()->cellToCoord(x1Index, y1Index, &x1, &y1);
			if (((3 * ny - 3 * y1Index) >= (x1Index*sqrt(3))) && ((y1Index - ny) >= (-x1Index*sqrt(3))) && (pow(x1Index, 2.0) + pow(y1Index - ny, 2.0) <= pow(a + 3, 2.0)))//a+3��ԭ��ʹ���߸�Բ��
			{
				colorMap->data()->setCell(x1Index, y1Index, 0);
				map2[x1Index][y1Index] = tag0;//map2�����������ڵĵ㱻��ʼ��Ϊtag0
			}
			else
			{
				colorMap->data()->setCell(x1Index, y1Index, 300);
				map2[x1Index][y1Index] = 0;
			}
		}
	}

	// Ϊ�ж�Ӧ�������ɢ�㸳ǿ��ֵ
	for (int p = 0; p<31; p++)
	{
		angle = p + 30;
		for (int q = 0; q<605; q++)
		{
			xindex = ceil(q*a*cos(angle*M_PI / 180) / 604);
			yindex = ceil(q*a*sin(angle*M_PI / 180) / 604);
			buf = input[p * 605 + q];
			//�ظ���ֵ�Ĵ����Ե������ص��ظ���ֵʱ��ȡ����ֵ��Ϊ����ֵ
			if (map2[yindex][ny - 1 - xindex] == tag0)//���������ǰû������ֵ
			{
				colorMap->data()->setCell(yindex, ny - 1 - xindex, buf);
				map2[yindex][ny - 1 - xindex] = tag1;
			}
			else
			{
				if ((colorMap->data()->cell(yindex, ny - 1 - xindex))<buf)
					colorMap->data()->setCell(yindex, ny - 1 - xindex, buf);
			}
		}
	}

	//�Ի�ͼ�����ڵ�û��ֵ�ĵ��ֵ
	//����Ϊ��ֵ�㷨
	//IDW
	double xinsert, yinsert, val = 0;
	int count = 1, step1, step2;
	double beta = 2.0;
	double di, d0 = 0, vi, wi, w0 = 0;
	for (int xIndex = 0; xIndex<nx; xIndex++)
	{
		for (int yIndex = 0; yIndex<ny; yIndex++)
		{
			colorMap->data()->cellToCoord(xIndex, yIndex, &xinsert, &yinsert);

			if ((map2[xIndex][yIndex] == tag0))//�������������ڵĵ㵫�ǻ�û�в�ֵ�Ļ�
			{
				for (int n = 1; n<radius + 1; n++)
				{
					for (step1 = -n; step1<n + 1; step1++)
					{
						for (step2 = -n; step2<n + 1; step2++)
						{
							if ((map2[xIndex + step1][yIndex + step2] == tag1))
							{
								di = 1 / (pow(step1, beta) + pow(step2, beta));
								d0 = d0 + di;
								vi = colorMap->data()->cell(xIndex + step1, yIndex + step2);
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
				colorMap->data()->setCell(xIndex, yIndex, val);

				count = 1;
				val = 0;
				d0 = 0;
				w0 = 0;
			}
		}
	}
	if (flag == 1)
	{
		qDebug() << "insert completed!" << endl;
	}
	ui.qCustomPlot->replot();
}

void MainWindow::timeupdate()
{
	QTime time = QTime::currentTime();
	QString timestr = time.toString("hh:mm:ss");
	ui.statusBar->showMessage(QString(timestr));
}

void MainWindow::material()
{
	int a = ui.materialbox->currentIndex();
	qDebug() << a;
	switch (a)
	{
	case 0:ui.vol->display(3000); break;//ÿ�䶼Ҫ��break�����һֱִ�е����һ��
	case 1:ui.vol->display(2700); break;
	case 2:ui.vol->display(1500); break;
	}
}

MainWindow::~MainWindow()
{

}
