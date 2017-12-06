/********************************************************************************
** Form generated from reading UI file 'Migrate3.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIGRATE3_H
#define UI_MIGRATE3_H

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

class Ui_Migrate3Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Migrate3Class)
    {
        if (Migrate3Class->objectName().isEmpty())
            Migrate3Class->setObjectName(QStringLiteral("Migrate3Class"));
        Migrate3Class->resize(600, 400);
        menuBar = new QMenuBar(Migrate3Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Migrate3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Migrate3Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Migrate3Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Migrate3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Migrate3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Migrate3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Migrate3Class->setStatusBar(statusBar);

        retranslateUi(Migrate3Class);

        QMetaObject::connectSlotsByName(Migrate3Class);
    } // setupUi

    void retranslateUi(QMainWindow *Migrate3Class)
    {
        Migrate3Class->setWindowTitle(QApplication::translate("Migrate3Class", "Migrate3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Migrate3Class: public Ui_Migrate3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIGRATE3_H
