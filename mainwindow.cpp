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
UA_Client *client = UA_Client_new();//create a OPC UA client

std::string get_str_to_variant (UA_Variant *var)
{
    auto str = (UA_String *)var->data;
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
    if (status==1)
    {
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));
        UA_Client_connect(client, "opc.tcp://localhost:4880");  //connect to server
        updatetimer = new QTimer(this);
        connect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        updatetimer->start(100);
    }
    else
    {
        disconnect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        UA_Client_disconnect(client);
    }




}

void MainWindow::UpdateTimerTick()
{
    ReadData(client);
}

void MainWindow::Clock()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->lnETime->setText(time_text);



}

void MainWindow::ReadData(UA_Client *client)
{
    UA_Variant value;   //create a variable to receive data
    // Get Name
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/LenName"), &value);
    byte len = *(UA_Byte*)value.data; // Get length of the robot name
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), &value);
    sName = get_str_to_variant(&value);
    QString strName = QString::fromStdString(sName);
    strName.resize(len-1);
    ui->lnERecv_Name->setText(strName);
    // Get Mode
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Mode"), &value);
    nMode = *(UA_Int32*)value.data ;
    QString R1Mode = QString::number(nMode);
    ui->lnERecv_Mode->setText(R1Mode);
    //Get Position
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Position"), &value);
    dPosition = *(UA_Double*)value.data ;
    QString R1Pos = QString::number(dPosition);
    ui->lnERecv_Pos->setText(R1Pos);
    //Get Status
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Status"), &value);
    bStatus = *(UA_Boolean*)value.data;
    QString R1Status = QString::number(bStatus);
    ui->lnERecv_Stt->setText(R1Status);
    //Get Temperature
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Temperature"), &value);
    dTemperature = *(UA_Double*)value.data;
    QString R1Temp = QString::number(dTemperature);
    ui->lnERecv_Temp->setText(R1Temp);
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

