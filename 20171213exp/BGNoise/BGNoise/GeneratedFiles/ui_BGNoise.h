/********************************************************************************
** Form generated from reading UI file 'BGNoise.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BGNOISE_H
#define UI_BGNOISE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_BGNoiseClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *plot1;
    QCustomPlot *plot2;
    QLabel *label2;
    QLabel *label1;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BGNoiseClass)
    {
        if (BGNoiseClass->objectName().isEmpty())
            BGNoiseClass->setObjectName(QStringLiteral("BGNoiseClass"));
        BGNoiseClass->resize(1477, 803);
        QFont font;
        font.setPointSize(14);
        BGNoiseClass->setFont(font);
        centralWidget = new QWidget(BGNoiseClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        plot1 = new QCustomPlot(centralWidget);
        plot1->setObjectName(QStringLiteral("plot1"));
        plot1->setGeometry(QRect(20, 30, 700, 700));
        plot2 = new QCustomPlot(centralWidget);
        plot2->setObjectName(QStringLiteral("plot2"));
        plot2->setGeometry(QRect(730, 30, 700, 700));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(730, 10, 131, 21));
        label2->setFont(font);
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(20, 10, 111, 21));
        BGNoiseClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BGNoiseClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1477, 23));
        BGNoiseClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BGNoiseClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BGNoiseClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BGNoiseClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BGNoiseClass->setStatusBar(statusBar);

        retranslateUi(BGNoiseClass);

        QMetaObject::connectSlotsByName(BGNoiseClass);
    } // setupUi

    void retranslateUi(QMainWindow *BGNoiseClass)
    {
        BGNoiseClass->setWindowTitle(QApplication::translate("BGNoiseClass", "BGNoise", Q_NULLPTR));
        label2->setText(QApplication::translate("BGNoiseClass", "TextLabel", Q_NULLPTR));
        label1->setText(QApplication::translate("BGNoiseClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BGNoiseClass: public Ui_BGNoiseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BGNOISE_H
