/********************************************************************************
** Form generated from reading UI file 'DataExport.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAEXPORT_H
#define UI_DATAEXPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataExportClass
{
public:
    QWidget *centralWidget;
    QLCDNumber *encoder0;
    QLabel *label1;
    QLCDNumber *encoder1;
    QLabel *label2;
    QLCDNumber *encoder;
    QLabel *label3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DataExportClass)
    {
        if (DataExportClass->objectName().isEmpty())
            DataExportClass->setObjectName(QStringLiteral("DataExportClass"));
        DataExportClass->resize(556, 384);
        centralWidget = new QWidget(DataExportClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        encoder0 = new QLCDNumber(centralWidget);
        encoder0->setObjectName(QStringLiteral("encoder0"));
        encoder0->setGeometry(QRect(30, 50, 161, 51));
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(50, 20, 54, 12));
        encoder1 = new QLCDNumber(centralWidget);
        encoder1->setObjectName(QStringLiteral("encoder1"));
        encoder1->setGeometry(QRect(320, 50, 161, 51));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(320, 20, 54, 12));
        encoder = new QLCDNumber(centralWidget);
        encoder->setObjectName(QStringLiteral("encoder"));
        encoder->setGeometry(QRect(190, 220, 161, 51));
        label3 = new QLabel(centralWidget);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setGeometry(QRect(210, 190, 54, 12));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 90, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(490, 90, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(360, 260, 54, 12));
        DataExportClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DataExportClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 23));
        DataExportClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DataExportClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DataExportClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DataExportClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DataExportClass->setStatusBar(statusBar);

        retranslateUi(DataExportClass);

        QMetaObject::connectSlotsByName(DataExportClass);
    } // setupUi

    void retranslateUi(QMainWindow *DataExportClass)
    {
        DataExportClass->setWindowTitle(QApplication::translate("DataExportClass", "DataExport", Q_NULLPTR));
        label1->setText(QApplication::translate("DataExportClass", "TextLabel", Q_NULLPTR));
        label2->setText(QApplication::translate("DataExportClass", "TextLabel", Q_NULLPTR));
        label3->setText(QApplication::translate("DataExportClass", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("DataExportClass", "mm", Q_NULLPTR));
        label_2->setText(QApplication::translate("DataExportClass", "mm", Q_NULLPTR));
        label_3->setText(QApplication::translate("DataExportClass", "mm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataExportClass: public Ui_DataExportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAEXPORT_H
