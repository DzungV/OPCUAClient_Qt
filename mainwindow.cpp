#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string.h>

#include <QDebug>
#include <QDateTime>

std::string sName;
//QString strName;
int nName;
double dPosition;
int nMode;
bool bStatus;
double dTemperature;
double dValue;

std::string get_str_to_variant (UA_Variant *var)
{
    auto str = (UA_String *)var->data;
//    int l = var->arrayLength;
//    for (int i; i< l; i++)
    return (char *)str->data;

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClientConnect(int status)
{
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    if (status==1)
        UA_Client_connect(client, "opc.tcp://localhost:4880");
    else
        UA_Client_disconnect(client);
    UA_Variant value;
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/LenName"), &value);
    byte len = *(UA_Byte*)value.data;

    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), &value);
//    char sName = *(UA_String*)value.data;
//    strName.sprintf("%s",sName);
    sName = get_str_to_variant(&value);

//    sName.length() = value.arrayLength;
    QString strName = QString::fromStdString(sName);
    strName.resize(len-1);

    ui->lnERecv_Name->setText(strName);
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Mode"), &value);
    nMode = *(UA_Int32*)value.data ;
    QString R1Mode = QString::number(nMode);
    ui->lnERecv_Mode->setText(R1Mode);
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Position"), &value);
    dPosition = *(UA_Double*)value.data ;
    QString R1Pos = QString::number(dPosition);
    ui->lnERecv_Pos->setText(R1Pos);
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Status"), &value);
    bStatus = *(UA_Boolean*)value.data;
    QString R1Status = QString::number(bStatus);
    ui->lnERecv_Stt->setText(R1Status);
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Temperature"), &value);
    dTemperature = *(UA_Double*)value.data;
    QString R1Temp = QString::number(dTemperature);
    ui->lnERecv_Temp->setText(R1Temp);
}

void MainWindow::UpdateTimerTick()
{


}

void MainWindow::Clock()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->lnETime->setText(time_text);



}


void MainWindow::on_btnStart_clicked()
{
    ClientConnect(1);
    ui->lbSttMsg->setText("Logging Started and Connected to OPC Server");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(Clock()));
    timer->start(1000);



}


void MainWindow::on_btnStop_clicked()
{
    ui->lbSttMsg->setText("Logging Stopped and Disconnected from OPC Server");
    ClientConnect(0);
    timer->stop();

}

