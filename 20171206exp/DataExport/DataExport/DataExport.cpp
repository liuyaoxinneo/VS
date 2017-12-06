#include "DataExport.h"
#include "qdebug.h"
#include "qfile.h"

int n = 0;
int encoderbuf;

DataExport::DataExport(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	net.tcp_connect("192.168.1.215");
	net.udp_connect();//������ͨ��UDP��ʽ����
	net.enable_data_transfer(true);//Ϊtrue���������ݴ���

	connect(&net, SIGNAL(capture_event(QByteArray)), this, SLOT(do_device_capture_event(QByteArray)));
	//�����źźͲ�
	ui.label1->setText("the previous");
	ui.label2->setText("the next");
	ui.label3->setText("movment");
}

void DataExport::do_device_capture_event(const QByteArray &data)
{
	//    ��ȡ��������Ϣ
	//    n=n+1;
	memcpy(&encoder, (data.data() + net.cur_group_point_qty() + 4 * 4), 4);
	//    qDebug()<<n<<encoder;
	if (encoder != encoderbuf)
	{
		ui.encoder0->display(encoderbuf);
		ui.encoder1->display(encoder);
		ui.encoder->display(encoder - encoderbuf);
		encoderbuf = encoder;

		if (encoder>0)
		{
			QString name = QString("data%1.txt")
				.arg(encoder);
			{
				unsigned char buffer[31][605];
				unsigned char txt[18755];
				int i, j;
				for (j = 0; j<31; j++)
				{
					for (i = 0; i<605; i++)
					{
						memcpy(&buffer[j][i], (data.data() + j * 637 + i), 1);
						txt[605 * j + i] = buffer[j][i];//���������õ�18755�ĵ�����ݷ���һά����txt[]��
					}
				}

				QFile file(name);
				if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
					return;
				QTextStream out(&file);
				for (int p = 0; p<18755; p++)
				{
					out << txt[p] << " " << "\n";
				}
				file.close();
				qDebug() << name << " has been written!";
			}
		}
	}
}
