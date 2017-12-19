#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DataExport.h"
#include"doppler_net.h"

class DataExport : public QMainWindow
{
	Q_OBJECT

public:
	DataExport(QWidget *parent = Q_NULLPTR);

public slots:
    void do_device_capture_event(const QByteArray &data);

private:
	Ui::DataExportClass ui;
	Doppler_net net;
	int encoder;
};
