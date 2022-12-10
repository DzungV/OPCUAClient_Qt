/********************************************************************************
** Form generated from reading UI file 'code_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODE_EDITOR_H
#define UI_CODE_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Code_Editor
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Code_Editor)
    {
        if (Code_Editor->objectName().isEmpty())
            Code_Editor->setObjectName(QString::fromUtf8("Code_Editor"));
        Code_Editor->resize(800, 600);
        menubar = new QMenuBar(Code_Editor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        Code_Editor->setMenuBar(menubar);
        centralwidget = new QWidget(Code_Editor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Code_Editor->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Code_Editor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Code_Editor->setStatusBar(statusbar);

        retranslateUi(Code_Editor);

        QMetaObject::connectSlotsByName(Code_Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Code_Editor)
    {
        Code_Editor->setWindowTitle(QCoreApplication::translate("Code_Editor", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Code_Editor: public Ui_Code_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODE_EDITOR_H
