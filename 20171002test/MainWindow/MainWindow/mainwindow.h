#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "doppler_net.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void dataimport();
	void timeupdate();
	void ascan();
	void material();
	void sscan();
	void initialization();

private:
	Ui::MainWindow ui;
	Doppler_net net;
};

#endif // MAINWINDOW_H
