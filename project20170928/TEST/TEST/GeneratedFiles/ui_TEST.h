/********************************************************************************
** Form generated from reading UI file 'TEST.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *qCustomPlot;
    QCustomPlot *qCustomPlot2;
    QComboBox *materialbox;
    QLabel *materials;
    QLCDNumber *gain;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(732, 497);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qCustomPlot = new QCustomPlot(centralWidget);
        qCustomPlot->setObjectName(QStringLiteral("qCustomPlot"));
        qCustomPlot->setEnabled(true);
        qCustomPlot->setGeometry(QRect(9, 9, 141, 433));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qCustomPlot->sizePolicy().hasHeightForWidth());
        qCustomPlot->setSizePolicy(sizePolicy);
        qCustomPlot2 = new QCustomPlot(centralWidget);
        qCustomPlot2->setObjectName(QStringLiteral("qCustomPlot2"));
        qCustomPlot2->setGeometry(QRect(158, 9, 451, 433));
        sizePolicy.setHeightForWidth(qCustomPlot2->sizePolicy().hasHeightForWidth());
        qCustomPlot2->setSizePolicy(sizePolicy);
        materialbox = new QComboBox(centralWidget);
        materialbox->setObjectName(QStringLiteral("materialbox"));
        materialbox->setGeometry(QRect(620, 40, 91, 22));
        materials = new QLabel(centralWidget);
        materials->setObjectName(QStringLiteral("materials"));
        materials->setGeometry(QRect(620, 10, 54, 21));
        gain = new QLCDNumber(centralWidget);
        gain->setObjectName(QStringLiteral("gain"));
        gain->setGeometry(QRect(620, 90, 101, 51));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        materials->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
