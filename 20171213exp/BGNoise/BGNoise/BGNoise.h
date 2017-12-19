#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BGNoise.h"

class BGNoise : public QMainWindow
{
	Q_OBJECT

public:
	BGNoise(QWidget *parent = Q_NULLPTR);

	public slots:
	void dataimport();
	void nc();

private:
	Ui::BGNoiseClass ui;
};
