#include "Migrate2.h"

Migrate2::Migrate2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	net.tcp_connect("192.168.1.215");//������ͨ��tcp����
	net.udp_connect();//������ͨ��UDP��ʽ����
	net.enable_data_transfer(true);//Ϊtrue���������ݴ���

	connect(&net, SIGNAL(capture_event(QByteArray)), this, SLOT(do_device_capture_event(QByteArray)));
	//�����źźͲ�

	//��������
	setWindowTitle("PHASCAN�������");//���ڼӱ���

	//�Խ���ͼ�ĳ�ʼ����������
	//aɨ�ĳ�ʼ��
	ui.qCustomPlot2->addGraph();//��qcustomplot�������һ������
	ui.qCustomPlot2->graph(0)->setPen(QPen(QColor(0, 0, 125)));//����aɨ����ɫΪ����
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

	//sɨ�ĳ�ʼ����һ����
	ui.qCustomPlot->axisRect()->setupFullAxesBox(true);//ʹ4���������ʾ

	//ui��ʼ����һ����
	//ѡ����ʾ�Ƕ�
	ui.label1->setText("�Ƕ�");
	ui.angle_spinBox->setRange(30, 60);
	ui.angle_spinBox->setSingleStep(1);

	//ѡ������
	ui.gainnumber->setRange(0.0, 100.0);
	ui.gainnumber->setValue((net.gain())*0.1);//��ȡĿǰ���������ã���Ϊ�����ĳ�ֵ
	ui.gainnumber->setSingleStep(10);
	ui.gainlabel->setText("����");

	//������Ϣ������....
	ui.vol->display(net.velocity());
	//a%,DA,PA,SA ��ʲô��˼����
}
