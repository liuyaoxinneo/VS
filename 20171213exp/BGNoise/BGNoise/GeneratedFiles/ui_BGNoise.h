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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BGNoiseClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BGNoiseClass)
    {
        if (BGNoiseClass->objectName().isEmpty())
            BGNoiseClass->setObjectName(QStringLiteral("BGNoiseClass"));
        BGNoiseClass->resize(600, 400);
        menuBar = new QMenuBar(BGNoiseClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BGNoiseClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BGNoiseClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BGNoiseClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BGNoiseClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BGNoiseClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BGNoiseClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BGNoiseClass->setStatusBar(statusBar);

        retranslateUi(BGNoiseClass);

        QMetaObject::connectSlotsByName(BGNoiseClass);
    } // setupUi

    void retranslateUi(QMainWindow *BGNoiseClass)
    {
        BGNoiseClass->setWindowTitle(QApplication::translate("BGNoiseClass", "BGNoise", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BGNoiseClass: public Ui_BGNoiseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BGNOISE_H
