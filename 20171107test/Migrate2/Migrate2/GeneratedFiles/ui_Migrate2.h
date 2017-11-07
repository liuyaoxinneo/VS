/********************************************************************************
** Form generated from reading UI file 'Migrate2.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIGRATE2_H
#define UI_MIGRATE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE

class Ui_Migrate2Class
{
public:
    QWidget *centralWidget;
    QCustomPlot *qCustomPlot;
    QCustomPlot *qCustomPlot2;
    QSpinBox *angle_spinBox;
    QLabel *label1;
    QDoubleSpinBox *gainnumber;
    QLabel *gainlabel;
    QLCDNumber *vol;
    QLabel *vollabel;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *Migrate2Class)
    {
        if (Migrate2Class->objectName().isEmpty())
            Migrate2Class->setObjectName(QStringLiteral("Migrate2Class"));
        Migrate2Class->resize(710, 710);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Migrate2Class->sizePolicy().hasHeightForWidth());
        Migrate2Class->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(Migrate2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qCustomPlot = new QCustomPlot(centralWidget);
        qCustomPlot->setObjectName(QStringLiteral("qCustomPlot"));
        qCustomPlot->setGeometry(QRect(10, 210, 591, 441));
        qCustomPlot2 = new QCustomPlot(centralWidget);
        qCustomPlot2->setObjectName(QStringLiteral("qCustomPlot2"));
        qCustomPlot2->setGeometry(QRect(10, 0, 591, 201));
        angle_spinBox = new QSpinBox(qCustomPlot2);
        angle_spinBox->setObjectName(QStringLiteral("angle_spinBox"));
        angle_spinBox->setGeometry(QRect(520, 10, 61, 22));
        label1 = new QLabel(qCustomPlot2);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(480, 10, 31, 21));
        gainnumber = new QDoubleSpinBox(centralWidget);
        gainnumber->setObjectName(QStringLiteral("gainnumber"));
        gainnumber->setGeometry(QRect(610, 40, 91, 31));
        gainlabel = new QLabel(centralWidget);
        gainlabel->setObjectName(QStringLiteral("gainlabel"));
        gainlabel->setGeometry(QRect(610, 20, 81, 20));
        vol = new QLCDNumber(centralWidget);
        vol->setObjectName(QStringLiteral("vol"));
        vol->setGeometry(QRect(610, 100, 91, 31));
        vollabel = new QLabel(centralWidget);
        vollabel->setObjectName(QStringLiteral("vollabel"));
        vollabel->setGeometry(QRect(610, 80, 91, 16));
        Migrate2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Migrate2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Migrate2Class->setStatusBar(statusBar);
        menuBar = new QMenuBar(Migrate2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 710, 23));
        Migrate2Class->setMenuBar(menuBar);

        retranslateUi(Migrate2Class);

        QMetaObject::connectSlotsByName(Migrate2Class);
    } // setupUi

    void retranslateUi(QMainWindow *Migrate2Class)
    {
        Migrate2Class->setWindowTitle(QApplication::translate("Migrate2Class", "Migrate2", Q_NULLPTR));
        label1->setText(QApplication::translate("Migrate2Class", "angle", Q_NULLPTR));
        gainlabel->setText(QApplication::translate("Migrate2Class", "\345\242\236\347\233\212\357\274\210dB\357\274\211", Q_NULLPTR));
        vollabel->setText(QApplication::translate("Migrate2Class", "\345\275\223\345\211\215\345\243\260\351\200\237\357\274\210m/s\357\274\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Migrate2Class: public Ui_Migrate2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIGRATE2_H
