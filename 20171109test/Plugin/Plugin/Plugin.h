#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Plugin.h"

class Plugin : public QMainWindow
{
	Q_OBJECT

public:
	Plugin(QWidget *parent = Q_NULLPTR);

private:
	Ui::PluginClass ui;
};
