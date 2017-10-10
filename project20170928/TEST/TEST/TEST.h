#pragma once
#ifndef TEST_H
#define TEST_H

#include <QtWidgets/QMainWindow>

namespace Ui {
	class TEST;
}

class TEST : public QMainWindow
{
	Q_OBJECT

public:
	explicit TEST(QWidget *parent = 0);
	~TEST();
	
public slots:
void material();


private:
	Ui::TEST *ui;
};

#endif