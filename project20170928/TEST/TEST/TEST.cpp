#include "TEST.h"
#include""

TEST::TEST(QWidget *parent): 
	QMainWindow(parent)
{
	ui.setupUi(this);
}
TEST::~TEST()
{
	delete ui;
}