#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FilePrefix.h"

class FilePrefix : public QMainWindow
{
	Q_OBJECT

public:
	FilePrefix(QWidget *parent = Q_NULLPTR);

private:
	Ui::FilePrefixClass ui;
};
