/********************************************************************************
** Form generated from reading UI file 'Plugin.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGIN_H
#define UI_PLUGIN_H

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

class Ui_PluginClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PluginClass)
    {
        if (PluginClass->objectName().isEmpty())
            PluginClass->setObjectName(QStringLiteral("PluginClass"));
        PluginClass->resize(600, 400);
        centralWidget = new QWidget(PluginClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PluginClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PluginClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        PluginClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PluginClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PluginClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PluginClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PluginClass->setStatusBar(statusBar);

        retranslateUi(PluginClass);

        QMetaObject::connectSlotsByName(PluginClass);
    } // setupUi

    void retranslateUi(QMainWindow *PluginClass)
    {
        PluginClass->setWindowTitle(QApplication::translate("PluginClass", "Plugin", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PluginClass: public Ui_PluginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGIN_H
