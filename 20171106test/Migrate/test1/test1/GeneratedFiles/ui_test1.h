/********************************************************************************
** Form generated from reading UI file 'test1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST1_H
#define UI_TEST1_H

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

class Ui_test1Class
{
public:
    QWidget *centralWidget;
    QCustomPlot *qCustomPlot;
    QCustomPlot *qCustomPlot2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test1Class)
    {
        if (test1Class->objectName().isEmpty())
            test1Class->setObjectName(QStringLiteral("test1Class"));
        test1Class->resize(733, 717);
        centralWidget = new QWidget(test1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qCustomPlot = new QCustomPlot(centralWidget);
        qCustomPlot->setObjectName(QStringLiteral("qCustomPlot"));
        qCustomPlot->setGeometry(QRect(200, 40, 521, 611));
        qCustomPlot2 = new QCustomPlot(centralWidget);
        qCustomPlot2->setObjectName(QStringLiteral("qCustomPlot2"));
        qCustomPlot2->setGeometry(QRect(10, 40, 181, 611));
        test1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(test1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 733, 23));
        test1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        test1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(test1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        test1Class->setStatusBar(statusBar);

        retranslateUi(test1Class);

        QMetaObject::connectSlotsByName(test1Class);
    } // setupUi

    void retranslateUi(QMainWindow *test1Class)
    {
        test1Class->setWindowTitle(QApplication::translate("test1Class", "test1", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class test1Class: public Ui_test1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST1_H
