#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Migrate3.h"
#include"doppler_net.h"

class Migrate3 : public QMainWindow
{
	Q_OBJECT

public:
	Migrate3(QWidget *parent = Q_NULLPTR);

private:
	Ui::Migrate3Class ui;
	Doppler_net net;
};
