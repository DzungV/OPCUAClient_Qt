#include "mainwindow.h"
#include "protocol.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string.h>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

std::string sName;
byte len;
//QString strName;
double dx;
double dy;
double dz;
double droll;
double dpitch;
double dyaw;
double dtheta1;
double dtheta2;
double dtheta4;
double dPosition;




QString STX = "2";
QString ETX = "3";

QString no_joint;
QString servostt;
QString direction;
QString coords;
QString StrPacketData;

double dd3;
UA_Variant* myVariant = UA_Variant_new();


UA_Client *client = UA_Client_new();//create a OPC UA client



void set_str_to_variant(UA_Variant *var, char stdPackData[]) {
//    char stdPackData[] = "delta";
    auto ua_PackData = UA_STRING(stdPackData);
    UA_Variant_setScalarCopy(var, &ua_PackData, &UA_TYPES[UA_TYPES_STRING]);
}

std::string get_str_to_variant (UA_Variant *var)
{
    auto str = (UA_String *)var->data;
    return ((char *)str->data);

}
int getlength (UA_Variant *var)
{
    auto str = (UA_String *)var->data;
    return (str->length);

}

int checkprogsend (QString &strPackData)
{
    int chck = 0;
    UA_Variant value;
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/Name"), &value);
    sName = get_str_to_variant(&value);
    len = getlength(&value);
    QString strName = QString::fromStdString(sName);
    strName.resize(len);
    QString strToFind = ";";
    QString Crc = strName.mid(strName.indexOf(strToFind)+strToFind.length()-1);
    int nr = Crc.toInt();
    QString cmd = strName.mid(1,6);
    Crc = strPackData.mid(strPackData.indexOf(strToFind)+strToFind.length()-1);
    int ns = Crc.toInt();
    if (cmd == "ACK,OK")
    {
        if (nr == ns)
            chck = 1;
        else
            chck = 0;
    }
    else
        chck = 0;
    return chck;

}

QString ChooseCoords (QString Coords)
{
    return Coords;
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
        updatetimer->start(10);
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
//     Get Name
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/LenName"), &value);
//    byte len = *(UA_Byte*)value.data; // Get length of the robot name
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/Name"), &value);

//    sName = get_str_to_variant(&value);
//    len = getlength(&value);
//    QString strName = QString::fromStdString(sName);
//    strName.resize(len);
//    ui->lnESend_Name->setText(strName);
//    // Get Mode
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Mode"), &value);
//    nMode = *(UA_Int32*)value.data ;
//    QString R1Mode = QString::number(nMode);
//    ui->lnERecv_Mode->setText(R1Mode);
//    //Get Position
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Position"), &value);
    dPosition = *(UA_Double*)value.data ;
    QString R1Pos = QString::number(dPosition);
    ui->lnESend_Pos->setText(R1Pos);
//    //Get Status
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Status"), &value);
//    bStatus = *(UA_Boolean*)value.data;
//    QString R1Status = QString::number(bStatus);
//    ui->lnERecv_Stt->setText(R1Status);
//    //Get Temperature
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Temperature"), &value);
//    dTemperature = *(UA_Double*)value.data;
//    QString R1Temp = QString::number(dTemperature);
//    ui->lnERecv_Temp->setText(R1Temp);
    //x
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/x"), &value);
    dx = *(UA_Double*)value.data ;
    QString R1x = QString::number(dx);
    ui->lnERecv_x->setText(R1x);
    //y
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/y"), &value);
    dy = *(UA_Double*)value.data ;
    QString R1y = QString::number(dy);
    ui->lnERecv_y->setText(R1y);
    //z
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/z"), &value);
    dz = *(UA_Double*)value.data ;
    QString R1z = QString::number(dz);
    ui->lnERecv_z->setText(R1z);
    //roll
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/roll"), &value);
    droll = *(UA_Double*)value.data ;
    QString R1roll = QString::number(droll);
    ui->lnERecv_roll->setText(R1roll);
    //pitch
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/pitch"), &value);
    dpitch = *(UA_Double*)value.data ;
    QString R1pitch = QString::number(dpitch);
    ui->lnERecv_pitch->setText(R1pitch);
    //yaw
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/yaw"), &value);
    dyaw = *(UA_Double*)value.data ;
    QString R1yaw = QString::number(dyaw);
    ui->lnERecv_yaw->setText(R1yaw);
    //theta1
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta1"), &value);
    dtheta1 = *(UA_Double*)value.data ;
    QString R1theta1 = QString::number(dtheta1);
    ui->lnERecv_theta1->setText(R1theta1);
    //theta2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta2"), &value);
    dtheta2 = *(UA_Double*)value.data ;
    QString R1theta2 = QString::number(dtheta2);
    ui->lnERecv_theta2->setText(R1theta2);
    //d3
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/d3"), &value);
    dd3 = *(UA_Double*)value.data ;
    QString R1d3 = QString::number(dd3);
    ui->lnERecv_d3->setText(R1d3);
    //theta4
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), &value);
    dtheta4 = *(UA_Double*)value.data ;
    QString R1theta4 = QString::number(dtheta4);
    ui->lnERecv_theta4->setText(R1theta4);
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


void MainWindow::on_btnJ1_neg_pressed()
{


    no_joint = "1";
    direction = "-1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

//    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta1"), myVariant);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);
}


void MainWindow::on_btnJ1_neg_released()
{
    no_joint = "1";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

//    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta1"), myVariant);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);


}


void MainWindow::on_btnJ1_pos_pressed()
{

    no_joint = "1";
    direction = "+1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

//    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta1"), myVariant);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);
}


void MainWindow::on_btnJ1_pos_released()
{

    no_joint = "1";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

//    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta1"), myVariant);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);
}


void MainWindow::on_btnJ2_neg_pressed()
{
    no_joint = "2";
    direction = "-1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta2"), myVariant);


}


void MainWindow::on_btnJ2_neg_released()
{
    no_joint = "2";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta2"), myVariant);

}


void MainWindow::on_btnJ2_pos_pressed()
{
    no_joint = "2";
    direction = "+1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta2"), myVariant);


}


void MainWindow::on_btnJ2_pos_released()
{

    no_joint = "2";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta2"), myVariant);
}


void MainWindow::on_btnJ3_neg_pressed()
{
    no_joint = "3";
    direction = "-1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta3"), myVariant);


}


void MainWindow::on_btnJ3_neg_released()
{

    no_joint = "3";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta3"), myVariant);
}


void MainWindow::on_btnJ3_pos_pressed()
{
    no_joint = "3";
    direction = "+1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta3"), myVariant);


}


void MainWindow::on_btnJ3_pos_released()
{
    no_joint = "3";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta3"), myVariant);

}


void MainWindow::on_btnJ4_neg_pressed()
{
    no_joint = "4";
    direction = "-1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), myVariant);


}


void MainWindow::on_btnJ4_neg_released()
{
    no_joint = "4";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), myVariant);

}


void MainWindow::on_btnJ4_pos_pressed()
{
    no_joint = "4";
    direction = "+1";
    coords = ChooseCoords(coords);
    StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), myVariant);


}


void MainWindow::on_btnJ4_pos_released()
{
    no_joint = "4";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);

    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), myVariant);
}


void MainWindow::on_btnSVON_clicked()
{
    servostt = "1";
    StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);


}


void MainWindow::on_btnSVOFF_clicked()
{
    servostt = "0";
    StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(StrPacketData);

    QByteArray bPackData = StrPacketData.toLocal8Bit();
    char *chPackData = bPackData.data();
    set_str_to_variant(myVariant,chPackData);
    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);

}






void MainWindow::on_chbCoords_currentTextChanged(const QString &arg1)
{

    if (arg1 == "Joint Coordinates")
        coords = "1";
    else if (arg1 == "Cartesian Coordinates")
        coords = "2";
    else if (arg1 == "Tool Coordinates")
        coords = "3";
    else if (arg1 == "User Coordinates")
        coords = "4";


}


void MainWindow::on_btnSendProg_clicked()
{
    int curline = 1;



    QFile inputFile("lmove.txt");
    if(!inputFile.exists())
    {
        ui->lnESend_Name->setText("File not found");
        return;
    }
//    int line_count=0;
//    inputFile.open(QIODevice::ReadOnly);
//    QString line[100];
//    QTextStream incnt(&inputFile);
//    while( !incnt.atEnd())
//        {
//            line[line_count]=incnt.readLine();
//            line_count++;
//        }


    if (inputFile.open(QIODevice::ReadOnly))
    {

//       QString linecnt = QString::number(line_count);
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QString curlin= QString::number(curline);
          StrPacketData = QString("%1ASMW,%2,%3%4").arg(STX,line,curlin,ETX);
          protocol* ptr;
          ptr = getprotocolPtr();
          ptr->MakeCrcSVON(StrPacketData);
          QByteArray bPackData = StrPacketData.toLocal8Bit();
          char *chPackData = bPackData.data();
          set_str_to_variant(myVariant,chPackData);
          UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Name"), myVariant);
          int ncheck = checkprogsend(StrPacketData); // check if command sent
          if (ncheck == 1)
          {
              QThread::msleep(50);
              curline++;
              continue;
          }
          else
          {
              QMessageBox::about(this, "Error", "Error Sending Program");
          }

       }
       inputFile.close();
    }
    else
    {
        ui->lnESend_Name->setText("Error String");

    }
}

