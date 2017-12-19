#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BGNoise.h"

class BGNoise : public QMainWindow
{
	Q_OBJECT

public:
	BGNoise(QWidget *parent = Q_NULLPTR);

	public slots:
	void initial();
	void dataimport();
	void nc();
	void plot1(); 
	void plot2();

private:
	Ui::BGNoiseClass ui;
};
