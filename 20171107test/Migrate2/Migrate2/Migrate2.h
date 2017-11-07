#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Migrate2.h"
#include "doppler_net.h"

class Migrate2 : public QMainWindow
{
	Q_OBJECT

public:
	Migrate2(QWidget *parent = Q_NULLPTR);

private:
	Ui::Migrate2Class ui;
	Doppler_net net;
};
