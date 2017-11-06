#include "test1.h"
#include "ui_test1.h"

test1::test1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ͼһ��aɨ
	{   //������ݣ�������QVector��
		QVector<double> x(101), y1(101);
		for (int i = 0; i<101; i++)
		{
			x[i] = -i / 5;
			y1[i] = cos(M_PI*i / 180);
		}
		ui.qCustomPlot->addGraph();//��qcustomplot�������һ������
		ui.qCustomPlot->graph(0)->setData(y1, x);//Ϊ�����ߣ�����Ϊgraph0����������

												  //qcustomplot�ĸ�ʽ����
												  // configure right and top axis to show ticks but no labels:
		ui.qCustomPlot->xAxis2->setVisible(true);
		ui.qCustomPlot->xAxis2->setTickLabels(true);
		ui.qCustomPlot->xAxis->setTickLabels(false);
		ui.qCustomPlot->xAxis->setVisible(false);
		ui.qCustomPlot->yAxis->setVisible(true);
		ui.qCustomPlot->yAxis->setTickLabels(true);
		ui.qCustomPlot->yAxis2->setVisible(false);
		ui.qCustomPlot->yAxis2->setTickLabels(false);//�����ᣬ�����ϵı�ǩ�Ƿ�ɼ�

		ui.qCustomPlot->xAxis2->setLabel("y");
		ui.qCustomPlot->yAxis->setLabel("x");//Ϊ�������������ƣ�ͨ����������ӱ�ǩ����ʽ
		ui.qCustomPlot->xAxis->setRange(-11, 11);
		ui.qCustomPlot->yAxis->setRange(-10, 10);//������ʾ��Χ
		ui.qCustomPlot->graph(0)->setPen(QPen(Qt::blue)); // ����������ɫ
		ui.qCustomPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ���������ɫ

		ui.qCustomPlot->rescaleAxes();//�Զ����������С��ʹ����ʾ������Ӧ���ڱ仯
		ui.qCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//��ʾ����Ľ�����������ק�����ַŴ���С��ѡ��ĳ����
	}
	//ͼ����color map
	{   // configure axis rect:
		ui.qCustomPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
		ui.qCustomPlot2->axisRect()->setupFullAxesBox(true);//ʹ4���������ʾ
		ui.qCustomPlot2->xAxis->setLabel("x");
		ui.qCustomPlot2->yAxis->setLabel("y");

		// set up the QCPColorMap:����ɫͼ
		QCPColorMap *colorMap = new QCPColorMap(ui.qCustomPlot2->xAxis, ui.qCustomPlot2->yAxis);
		int nx = 200;
		int ny = 200;
		int a = 200;
		colorMap->data()->setSize(nx, ny); //ʹ��һ����nx * ny�����ݵ�
										   //    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

										   //colormap��ʼ��
										   //    double m, n;
										   //    for (int mIndex=0; mIndex<nx; ++mIndex)
										   //    {
										   //      for (int nIndex=0; nIndex<ny; ++nIndex)
										   //      {
										   //        colorMap->data()->cellToCoord(mIndex, nIndex, &m, &n);
										   //        if(mIndex!=0)
										   //        {
										   //        if((200-nIndex)/mIndex>=-sqrt(3)&&(200-nIndex)/mIndex<=-1/sqrt(3))
										   //        {if(pow((mIndex+0.0),2.0)+pow((nIndex-200.0),2.0)<=pow(a,2.0))
										   //              { colorMap->data()->setCell(mIndex, nIndex, 100);}}
										   //        }
										   //      }

										   //    }
										   // now we assign some data, by accessing the QCPColorMapData instance of the color map:
		double x, y, z;
		for (int xIndex = 0; xIndex<nx; ++xIndex)
		{
			for (int yIndex = 0; yIndex<ny; ++yIndex)
			{
				colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);

				//                if((pow(xIndex,2.0)+pow(yIndex-ny,2.0)<=pow(a,2.0))
				//                if((yIndex-ny)>=(-xIndex*sqrt(3)))
				if (((3 * ny - 3 * yIndex) >= (xIndex*sqrt(3))) && ((yIndex - ny) >= (-xIndex*sqrt(3))) && (pow(xIndex, 2.0) + pow(yIndex - ny, 2.0) <= pow(a, 2.0)))
				{
					double r = 2 * qSqrt(x*x + y*y) + 1e-2;
					z = 2 * x*(qCos(r + 3) / r - qSin(r + 2) / r);
					colorMap->data()->setCell(xIndex, yIndex, z);
				}
				else
					colorMap->data()->setCell(xIndex, yIndex, 0);
				// the B field strength of dipole radiation (modulo physical constants)
				//        colorMap->data()->setCell(xIndex, yIndex, 0);
			}
		}

		// add a color scale:
		//QCPColorScale *colorScale = new QCPColorScale(ui->qCustomPlot2);
		//ui->qCustomPlot2->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
		//colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
		//colorMap->setColorScale(colorScale); // associate the color map with the color scale
		//colorScale->axis()->setLabel("����");

		//// set the color gradient of the color map to one of the presets:
		//colorMap->setGradient(QCPColorGradient::gpPolar);
		//// we could have also created a QCPColorGradient instance and added own colors to
		//// the gradient, see the documentation of QCPColorGradient for what's possible.

		//// rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
		//colorMap->rescaleDataRange();

		//// make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
		//QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->qCustomPlot2);
		//ui->qCustomPlot2->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
		//colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

		ui.qCustomPlot2->rescaleAxes();
	}

	ui.qCustomPlot->replot();//ͼ���ػ棬���ڶ�̬��ͼ

	//ui.materials->setText("�Կ����");
	//QStringList materiallist;
	//materiallist << "Fe" << "Al" << "Wood";//ѡ�������������
	//ui->materialbox->addItems(materiallist);

}
