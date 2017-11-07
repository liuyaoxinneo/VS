#include "Migrate2.h"

Migrate2::Migrate2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	net.tcp_connect("192.168.1.215");//与仪器通过tcp连接
	net.udp_connect();//与仪器通过UDP方式连接
	net.enable_data_transfer(true);//为true则启动数据传输

	connect(&net, SIGNAL(capture_event(QByteArray)), this, SLOT(do_device_capture_event(QByteArray)));
	//连接信号和槽

	//窗口设置
	setWindowTitle("PHASCAN测量结果");//窗口加标题

	//试将画图的初始化放在这里
	//a扫的初始化
	ui.qCustomPlot2->addGraph();//向qcustomplot里面添加一条曲线
	ui.qCustomPlot2->graph(0)->setPen(QPen(QColor(0, 0, 125)));//设置a扫的颜色为深蓝
	ui.qCustomPlot2->graph(0)->setLineStyle(QCPGraph::LineStyle::lsStepCenter);//设置绘线类型
																				// 设置轴，和轴上的标签是否可见
	ui.qCustomPlot2->xAxis->setVisible(true);
	ui.qCustomPlot2->xAxis2->setVisible(false);
	ui.qCustomPlot2->yAxis->setVisible(true);
	ui.qCustomPlot2->yAxis2->setVisible(false);

	ui.qCustomPlot2->xAxis->setTickLabels(true);
	ui.qCustomPlot2->xAxis2->setTickLabels(false);
	ui.qCustomPlot2->yAxis->setTickLabels(true);
	ui.qCustomPlot2->yAxis2->setTickLabels(false);

	ui.qCustomPlot2->xAxis->setRange(0, 80);
	ui.qCustomPlot2->yAxis->setRange(0, 100);//设置y,x的范围
	ui.qCustomPlot2->xAxis->setLabel("深度(mm)");
	ui.qCustomPlot2->yAxis->setLabel("强度(%)");

	//s扫的初始化的一部分
	ui.qCustomPlot->axisRect()->setupFullAxesBox(true);//使4条轴均可显示

	//ui初始化的一部分
	//选择显示角度
	ui.label1->setText("角度");
	ui.angle_spinBox->setRange(30, 60);
	ui.angle_spinBox->setSingleStep(1);

	//选择增益
	ui.gainnumber->setRange(0.0, 100.0);
	ui.gainnumber->setValue((net.gain())*0.1);//获取目前的增益设置，作为调整的初值
	ui.gainnumber->setSingleStep(10);
	ui.gainlabel->setText("增益");

	//工件信息：声速....
	ui.vol->display(net.velocity());
	//a%,DA,PA,SA 是什么意思？？
}
