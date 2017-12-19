/********************************************************************************
** Form generated from reading UI file 'Plot.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_PlotClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *plot;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PlotClass)
    {
        if (PlotClass->objectName().isEmpty())
            PlotClass->setObjectName(QStringLiteral("PlotClass"));
        PlotClass->resize(1007, 935);
        centralWidget = new QWidget(PlotClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(10, 10, 981, 871));
        PlotClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlotClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1007, 23));
        PlotClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlotClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PlotClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PlotClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PlotClass->setStatusBar(statusBar);

        retranslateUi(PlotClass);

        QMetaObject::connectSlotsByName(PlotClass);
    } // setupUi

    void retranslateUi(QMainWindow *PlotClass)
    {
        PlotClass->setWindowTitle(QApplication::translate("PlotClass", "Plot", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlotClass: public Ui_PlotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
