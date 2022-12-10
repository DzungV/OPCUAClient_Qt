/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lbSttMsg;
    QPushButton *btnStart;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lnESend_Name;
    QLineEdit *lnESend_Pos;
    QLineEdit *lnESend_Mode;
    QLineEdit *lnESend_Stt;
    QLineEdit *lnESend_Temp;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *btnSVOFF;
    QPushButton *btnJ2_neg;
    QComboBox *chbCoords;
    QPushButton *btnJ4_neg;
    QPushButton *btnJ2_pos;
    QPushButton *btnJ4_pos;
    QPushButton *btnJ1_pos;
    QPushButton *btnJ3_pos;
    QPushButton *btnJ3_neg;
    QPushButton *btnJ1_neg;
    QPushButton *btnSVON;
    QLabel *label_17;
    QPushButton *btnSpeed_low;
    QPushButton *btnSpeed_med;
    QPushButton *btnSpeed_high;
    QPushButton *btnSpeed_top;
    QWidget *tab_2;
    QPushButton *btnSendProg;
    QPushButton *btnWriteProg;
    QPlainTextEdit *plainTxtEdProg;
    QPushButton *btnCompProg;
    QGroupBox *groupBox_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QLabel *label_10;
    QLabel *label_15;
    QLabel *label_8;
    QLineEdit *lnERecv_theta2;
    QLineEdit *lnERecv_z;
    QLabel *label_14;
    QLineEdit *lnERecv_x;
    QLineEdit *lnERecv_roll;
    QLineEdit *lnERecv_d3;
    QLineEdit *lnERecv_pitch;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_16;
    QLineEdit *lnERecv_theta4;
    QLineEdit *lnERecv_y;
    QLineEdit *lnERecv_theta1;
    QLabel *label_9;
    QLineEdit *lnERecv_yaw;
    QLabel *label_11;
    QWidget *tab_4;
    QLabel *label_2;
    QLineEdit *lnETime;
    QPushButton *btnStop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1478, 752);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lbSttMsg = new QLabel(centralwidget);
        lbSttMsg->setObjectName(QString::fromUtf8("lbSttMsg"));
        lbSttMsg->setGeometry(QRect(80, 20, 331, 20));
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(430, 20, 93, 29));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 100, 901, 591));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 81, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 63, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 180, 63, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 240, 63, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 290, 91, 20));
        lnESend_Name = new QLineEdit(groupBox);
        lnESend_Name->setObjectName(QString::fromUtf8("lnESend_Name"));
        lnESend_Name->setGeometry(QRect(10, 90, 131, 26));
        lnESend_Pos = new QLineEdit(groupBox);
        lnESend_Pos->setObjectName(QString::fromUtf8("lnESend_Pos"));
        lnESend_Pos->setGeometry(QRect(10, 150, 91, 26));
        lnESend_Mode = new QLineEdit(groupBox);
        lnESend_Mode->setObjectName(QString::fromUtf8("lnESend_Mode"));
        lnESend_Mode->setGeometry(QRect(10, 200, 81, 26));
        lnESend_Stt = new QLineEdit(groupBox);
        lnESend_Stt->setObjectName(QString::fromUtf8("lnESend_Stt"));
        lnESend_Stt->setGeometry(QRect(10, 260, 81, 26));
        lnESend_Temp = new QLineEdit(groupBox);
        lnESend_Temp->setObjectName(QString::fromUtf8("lnESend_Temp"));
        lnESend_Temp->setGeometry(QRect(10, 320, 71, 26));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(140, 20, 751, 561));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        btnSVOFF = new QPushButton(tab);
        btnSVOFF->setObjectName(QString::fromUtf8("btnSVOFF"));
        btnSVOFF->setGeometry(QRect(120, 300, 93, 29));
        btnJ2_neg = new QPushButton(tab);
        btnJ2_neg->setObjectName(QString::fromUtf8("btnJ2_neg"));
        btnJ2_neg->setGeometry(QRect(10, 110, 93, 29));
        chbCoords = new QComboBox(tab);
        chbCoords->addItem(QString());
        chbCoords->addItem(QString());
        chbCoords->addItem(QString());
        chbCoords->addItem(QString());
        chbCoords->addItem(QString());
        chbCoords->setObjectName(QString::fromUtf8("chbCoords"));
        chbCoords->setGeometry(QRect(10, 10, 191, 26));
        btnJ4_neg = new QPushButton(tab);
        btnJ4_neg->setObjectName(QString::fromUtf8("btnJ4_neg"));
        btnJ4_neg->setGeometry(QRect(10, 240, 93, 29));
        btnJ2_pos = new QPushButton(tab);
        btnJ2_pos->setObjectName(QString::fromUtf8("btnJ2_pos"));
        btnJ2_pos->setGeometry(QRect(120, 110, 93, 29));
        btnJ4_pos = new QPushButton(tab);
        btnJ4_pos->setObjectName(QString::fromUtf8("btnJ4_pos"));
        btnJ4_pos->setGeometry(QRect(120, 240, 93, 29));
        btnJ1_pos = new QPushButton(tab);
        btnJ1_pos->setObjectName(QString::fromUtf8("btnJ1_pos"));
        btnJ1_pos->setGeometry(QRect(120, 50, 93, 29));
        btnJ3_pos = new QPushButton(tab);
        btnJ3_pos->setObjectName(QString::fromUtf8("btnJ3_pos"));
        btnJ3_pos->setGeometry(QRect(120, 170, 93, 29));
        btnJ3_neg = new QPushButton(tab);
        btnJ3_neg->setObjectName(QString::fromUtf8("btnJ3_neg"));
        btnJ3_neg->setGeometry(QRect(10, 170, 93, 29));
        btnJ1_neg = new QPushButton(tab);
        btnJ1_neg->setObjectName(QString::fromUtf8("btnJ1_neg"));
        btnJ1_neg->setGeometry(QRect(10, 50, 93, 29));
        btnSVON = new QPushButton(tab);
        btnSVON->setObjectName(QString::fromUtf8("btnSVON"));
        btnSVON->setGeometry(QRect(10, 300, 93, 29));
        label_17 = new QLabel(tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(300, 20, 63, 20));
        btnSpeed_low = new QPushButton(tab);
        btnSpeed_low->setObjectName(QString::fromUtf8("btnSpeed_low"));
        btnSpeed_low->setGeometry(QRect(290, 60, 93, 29));
        btnSpeed_med = new QPushButton(tab);
        btnSpeed_med->setObjectName(QString::fromUtf8("btnSpeed_med"));
        btnSpeed_med->setGeometry(QRect(290, 100, 93, 29));
        btnSpeed_high = new QPushButton(tab);
        btnSpeed_high->setObjectName(QString::fromUtf8("btnSpeed_high"));
        btnSpeed_high->setGeometry(QRect(290, 140, 93, 29));
        btnSpeed_top = new QPushButton(tab);
        btnSpeed_top->setObjectName(QString::fromUtf8("btnSpeed_top"));
        btnSpeed_top->setGeometry(QRect(290, 180, 93, 29));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        btnSendProg = new QPushButton(tab_2);
        btnSendProg->setObjectName(QString::fromUtf8("btnSendProg"));
        btnSendProg->setGeometry(QRect(540, 470, 131, 41));
        btnWriteProg = new QPushButton(tab_2);
        btnWriteProg->setObjectName(QString::fromUtf8("btnWriteProg"));
        btnWriteProg->setGeometry(QRect(30, 470, 131, 41));
        plainTxtEdProg = new QPlainTextEdit(tab_2);
        plainTxtEdProg->setObjectName(QString::fromUtf8("plainTxtEdProg"));
        plainTxtEdProg->setGeometry(QRect(10, 10, 721, 431));
        btnCompProg = new QPushButton(tab_2);
        btnCompProg->setObjectName(QString::fromUtf8("btnCompProg"));
        btnCompProg->setGeometry(QRect(280, 470, 151, 41));
        tabWidget->addTab(tab_2, QString());
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(930, 100, 531, 591));
        tabWidget_2 = new QTabWidget(groupBox_2);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(30, 40, 511, 391));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 190, 41, 20));
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(290, 140, 63, 20));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 90, 21, 20));
        lnERecv_theta2 = new QLineEdit(tab_3);
        lnERecv_theta2->setObjectName(QString::fromUtf8("lnERecv_theta2"));
        lnERecv_theta2->setGeometry(QRect(370, 90, 113, 26));
        lnERecv_z = new QLineEdit(tab_3);
        lnERecv_z->setObjectName(QString::fromUtf8("lnERecv_z"));
        lnERecv_z->setGeometry(QRect(110, 140, 113, 26));
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(290, 40, 63, 20));
        lnERecv_x = new QLineEdit(tab_3);
        lnERecv_x->setObjectName(QString::fromUtf8("lnERecv_x"));
        lnERecv_x->setGeometry(QRect(110, 40, 113, 26));
        lnERecv_roll = new QLineEdit(tab_3);
        lnERecv_roll->setObjectName(QString::fromUtf8("lnERecv_roll"));
        lnERecv_roll->setGeometry(QRect(110, 190, 113, 26));
        lnERecv_d3 = new QLineEdit(tab_3);
        lnERecv_d3->setObjectName(QString::fromUtf8("lnERecv_d3"));
        lnERecv_d3->setGeometry(QRect(370, 140, 113, 26));
        lnERecv_pitch = new QLineEdit(tab_3);
        lnERecv_pitch->setObjectName(QString::fromUtf8("lnERecv_pitch"));
        lnERecv_pitch->setGeometry(QRect(110, 240, 113, 26));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(30, 290, 63, 20));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(290, 90, 63, 20));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 40, 31, 20));
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(290, 190, 63, 20));
        lnERecv_theta4 = new QLineEdit(tab_3);
        lnERecv_theta4->setObjectName(QString::fromUtf8("lnERecv_theta4"));
        lnERecv_theta4->setGeometry(QRect(370, 180, 111, 31));
        lnERecv_y = new QLineEdit(tab_3);
        lnERecv_y->setObjectName(QString::fromUtf8("lnERecv_y"));
        lnERecv_y->setGeometry(QRect(110, 90, 113, 26));
        lnERecv_theta1 = new QLineEdit(tab_3);
        lnERecv_theta1->setObjectName(QString::fromUtf8("lnERecv_theta1"));
        lnERecv_theta1->setGeometry(QRect(370, 40, 113, 26));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 140, 31, 20));
        lnERecv_yaw = new QLineEdit(tab_3);
        lnERecv_yaw->setObjectName(QString::fromUtf8("lnERecv_yaw"));
        lnERecv_yaw->setGeometry(QRect(110, 290, 113, 26));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 240, 51, 20));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget_2->addTab(tab_4, QString());
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 60, 81, 20));
        lnETime = new QLineEdit(centralwidget);
        lnETime->setObjectName(QString::fromUtf8("lnETime"));
        lnETime->setGeometry(QRect(210, 60, 113, 26));
        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(430, 70, 93, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1478, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbSttMsg->setText(QCoreApplication::translate("MainWindow", "Connection Status Message", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "RobotSimData Send", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Command", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        btnSVOFF->setText(QCoreApplication::translate("MainWindow", "SERVO OFF", nullptr));
        btnJ2_neg->setText(QCoreApplication::translate("MainWindow", "J2-", nullptr));
        chbCoords->setItemText(0, QCoreApplication::translate("MainWindow", "Choose Coordinates", nullptr));
        chbCoords->setItemText(1, QCoreApplication::translate("MainWindow", "Joint Coordinates", nullptr));
        chbCoords->setItemText(2, QCoreApplication::translate("MainWindow", "Cartesian Coordinates", nullptr));
        chbCoords->setItemText(3, QCoreApplication::translate("MainWindow", "Tool Coordinates", nullptr));
        chbCoords->setItemText(4, QCoreApplication::translate("MainWindow", "User Coordinates", nullptr));

        btnJ4_neg->setText(QCoreApplication::translate("MainWindow", "J4-", nullptr));
        btnJ2_pos->setText(QCoreApplication::translate("MainWindow", "J2+", nullptr));
        btnJ4_pos->setText(QCoreApplication::translate("MainWindow", "J4+", nullptr));
        btnJ1_pos->setText(QCoreApplication::translate("MainWindow", "J1+", nullptr));
        btnJ3_pos->setText(QCoreApplication::translate("MainWindow", "J3+", nullptr));
        btnJ3_neg->setText(QCoreApplication::translate("MainWindow", "J3-", nullptr));
        btnJ1_neg->setText(QCoreApplication::translate("MainWindow", "J1- ", nullptr));
        btnSVON->setText(QCoreApplication::translate("MainWindow", "SERVO ON", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        btnSpeed_low->setText(QCoreApplication::translate("MainWindow", "LOW", nullptr));
        btnSpeed_med->setText(QCoreApplication::translate("MainWindow", "MEDIUM", nullptr));
        btnSpeed_high->setText(QCoreApplication::translate("MainWindow", "HIGH", nullptr));
        btnSpeed_top->setText(QCoreApplication::translate("MainWindow", "TOP", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "JOG", nullptr));
        btnSendProg->setText(QCoreApplication::translate("MainWindow", "Send Program", nullptr));
        btnWriteProg->setText(QCoreApplication::translate("MainWindow", "Write a Program", nullptr));
        plainTxtEdProg->setPlainText(QString());
        btnCompProg->setText(QCoreApplication::translate("MainWindow", "Compile Program", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "PROGRAM", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "RobotSimData Receive", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "roll", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "d3", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "theta1", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "yaw", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "theta2", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "x ", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "theta4", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "pitch", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "SCARA", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "DELTA", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TimeStamp", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
