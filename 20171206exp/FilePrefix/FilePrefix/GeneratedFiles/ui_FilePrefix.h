/********************************************************************************
** Form generated from reading UI file 'FilePrefix.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEPREFIX_H
#define UI_FILEPREFIX_H

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

class Ui_FilePrefixClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FilePrefixClass)
    {
        if (FilePrefixClass->objectName().isEmpty())
            FilePrefixClass->setObjectName(QStringLiteral("FilePrefixClass"));
        FilePrefixClass->resize(600, 400);
        menuBar = new QMenuBar(FilePrefixClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        FilePrefixClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FilePrefixClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FilePrefixClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(FilePrefixClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FilePrefixClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FilePrefixClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FilePrefixClass->setStatusBar(statusBar);

        retranslateUi(FilePrefixClass);

        QMetaObject::connectSlotsByName(FilePrefixClass);
    } // setupUi

    void retranslateUi(QMainWindow *FilePrefixClass)
    {
        FilePrefixClass->setWindowTitle(QApplication::translate("FilePrefixClass", "FilePrefix", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FilePrefixClass: public Ui_FilePrefixClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEPREFIX_H
