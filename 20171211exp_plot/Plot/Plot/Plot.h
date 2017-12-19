#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Plot.h"

class Plot : public QMainWindow
{
	Q_OBJECT

public:
	Plot(QWidget *parent = Q_NULLPTR);

	public slots:
	void initialization();
	void dataimport();
	void plot();

private:
	Ui::PlotClass ui;
};
