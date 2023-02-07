/********************************************************************************
** Form generated from reading UI file 'alarmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMDIALOG_H
#define UI_ALARMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AlarmDialog
{
public:
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *AlarmDialog)
    {
        if (AlarmDialog->objectName().isEmpty())
            AlarmDialog->setObjectName(QString::fromUtf8("AlarmDialog"));
        AlarmDialog->resize(646, 431);
        plainTextEdit = new QPlainTextEdit(AlarmDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 60, 611, 301));
        pushButton = new QPushButton(AlarmDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(520, 10, 101, 31));
        pushButton_2 = new QPushButton(AlarmDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(520, 380, 101, 31));

        retranslateUi(AlarmDialog);

        QMetaObject::connectSlotsByName(AlarmDialog);
    } // setupUi

    void retranslateUi(QDialog *AlarmDialog)
    {
        AlarmDialog->setWindowTitle(QCoreApplication::translate("AlarmDialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("AlarmDialog", "Reset Alarm", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AlarmDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlarmDialog: public Ui_AlarmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMDIALOG_H
