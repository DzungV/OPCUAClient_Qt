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
#include <QWidget>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QCloseEvent>
#include <QProcess>

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
int numclient;
int robotnum;
int pointlist[10];
QTableWidgetItem *jpoint;
QTableWidgetItem *wpoint;
QTableWidgetItem *getpoint;
//jpoint = new QTableWidgetItem;

const char* nodeid;
QString strCurJobName;
QString filepath;



char* chPacketData;



QString STX = "2";
QString ETX = "3";

QString no_joint;
QString servostt;
QString direction;
QString coords;
QString StrPacketData;
QString speed;

double dd3;
UA_Variant* myVariant = UA_Variant_new();
UA_Variant value;

UA_Client *client = UA_Client_new();//create a OPC UA client

UA_Int32 noclient;

// FUNCTION

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

const char* ChooseRobot (int robot)
{
    const char* node = NULL;
    if (robot == 1)
        node = "ns=4;s=Robot1/CMDSend";
    else if (robot == 2)
        node = "ns=4;s=Robot2/CMDSend";
    else if (robot == 3)
        node = "ns=4;s=Robot3/CMDSend";
    return node;
}

int checkprogsend (QString &strPackData)
{
    int chck = 0;
    UA_Variant value;
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/CMDAck"), &value);
    std::string ACK = get_str_to_variant(&value);
    int ACKlen = getlength(&value);
    QString strACK = QString::fromStdString(ACK);
    strACK.resize(ACKlen);
    QString strToFind = ";";
    QString Crc = strACK.mid(strACK.indexOf(strToFind)+1);
    Crc.chop(1);
    int nr = Crc.toInt();
    QString cmd = strACK.mid(1,6);
    QString strToFind1 = ";";
//    int n = strPackData.lastIndexOf(strToFind1);
    QString Crc1 = strPackData.mid(strPackData.indexOf(strToFind1)+1);
    Crc1.chop(1);
    int ns = Crc1.toInt();
    qDebug() << nr << ns;
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

char* PackData (QString strPackData)
{
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(strPackData);

    QByteArray bPackData = strPackData.toLocal8Bit();
    char *chPackData = bPackData.data();
    return chPackData;
}

QString checksend(QString strPackData)
{
    protocol* ptr;
    ptr = getprotocolPtr();
    ptr->MakeCrcSVON(strPackData);
    return strPackData;
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
        UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
        noclient = *(UA_Int32*)value.data ;
        noclient += 1;
        UA_Variant_setScalarCopy(myVariant, &noclient, &UA_TYPES[UA_TYPES_INT32]);
        UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), myVariant);

        //Create update timer
        updatetimer = new QTimer(this);
        connect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        updatetimer->start(10);
    }
    else if (status==0)
    {
        disconnect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));

        UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
        noclient = *(UA_Int32*)value.data ;
        noclient += -1;
        UA_Variant_setScalarCopy(myVariant, &noclient, &UA_TYPES[UA_TYPES_INT32]);
        UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), myVariant);

        UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
        numclient = *(UA_Int32*)value.data ;
        QString NoClient = QString::number(numclient);
        ui->lnENoclients->setText(NoClient);

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
       //create a variable to receive data
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
//    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Position"), &value);
//    dPosition = *(UA_Double*)value.data ;
//    QString R1Pos = QString::number(dPosition);
//    ui->lnESend_Pos->setText(R1Pos);
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
    // Number of clients
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
    numclient = *(UA_Int32*)value.data ;
    QString NoClient = QString::number(numclient);
    ui->lnENoclients->setText(NoClient);
    //SCARA Data
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
    //CMDAck
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/CMDAck"), &value);
    sName = get_str_to_variant(&value);
    len = getlength(&value);
    QString strName = QString::fromStdString(sName);
    strName.resize(len);
    ui->lnECmd->setText(strName);

    // DELTA Data
    //theta1
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta1"), &value);
    dtheta1 = *(UA_Double*)value.data ;
    QString R2theta1 = QString::number(dtheta1);
    ui->lnERecv_theta1_1->setText(R1theta1);
    //theta2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta2"), &value);
    dtheta2 = *(UA_Double*)value.data ;
    QString R2theta2 = QString::number(dtheta2);
    ui->lnERecv_theta2_1->setText(R1theta2);
    //theta3
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta3"), &value);
    dd3 = *(UA_Double*)value.data ;
    QString R2theta3 = QString::number(dd3);
    ui->lnERecv_theta3_1->setText(R1d3);
    //CMDAck
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/CMDAck"), &value);
    sName = get_str_to_variant(&value);
    len = getlength(&value);
    QString strName1 = QString::fromStdString(sName);
    strName1.resize(len);
    ui->lnECmd1->setText(strName1);
}

// CONNECTION

void MainWindow::on_btnStart_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Caution", "Open the server first!!!",
                                                            QMessageBox::Yes | QMessageBox::No);
    if (ans == QMessageBox::Yes)
    {
        ClientConnect(1);
        ui->lbSttMsg->setText("Logging Started and Connected to OPC Server");
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this,SLOT(Clock()));
        timer->start(1000);
    }
    else
    {
        ui->lbSttMsg->setText("Server is not open");
    }


}


void MainWindow::on_btnStop_clicked()
{
    ui->lbSttMsg->setText("Logging Stopped and Disconnected from OPC Server");
    ClientConnect(0);
    timer->stop();

}


// JOG TAB

void MainWindow::on_btnJ1_neg_pressed()
{


    no_joint = "1";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
    }

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ1_neg_released()
{
    no_joint = "1";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);


}


void MainWindow::on_btnJ1_pos_pressed()
{

    no_joint = "1";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
    }

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ1_pos_released()
{

    no_joint = "1";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ2_neg_pressed()
{
    no_joint = "2";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }


}


void MainWindow::on_btnJ2_neg_released()
{
    no_joint = "2";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

}


void MainWindow::on_btnJ2_pos_pressed()
{
    no_joint = "2";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ2_pos_released()
{

    no_joint = "2";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ3_neg_pressed()
{
    no_joint = "3";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

    }
}


void MainWindow::on_btnJ3_neg_released()
{

    no_joint = "3";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ3_pos_pressed()
{
    no_joint = "3";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }


}


void MainWindow::on_btnJ3_pos_released()
{
    no_joint = "3";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

}


void MainWindow::on_btnJ4_neg_pressed()
{
    no_joint = "4";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ4_neg_released()
{
    no_joint = "4";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

}


void MainWindow::on_btnJ4_pos_pressed()
{
    no_joint = "4";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

    }

}


void MainWindow::on_btnJ4_pos_released()
{
    no_joint = "4";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}

void MainWindow::on_btnJ5_neg_pressed()
{
    no_joint = "5";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ5_neg_released()
{
    no_joint = "5";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ5_pos_pressed()
{
    no_joint = "5";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ5_pos_released()
{
    no_joint = "5";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ6_neg_pressed()
{
    no_joint = "6";
    direction = "-1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ6_neg_released()
{
    no_joint = "6";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnJ6_pos_pressed()
{
    no_joint = "6";
    direction = "+1";
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        StrPacketData = QString("%1JOGJ,%2,%3,%4%5").arg(STX,coords,no_joint,direction,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    }
}


void MainWindow::on_btnJ6_pos_released()
{
    no_joint = "6";
    StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}



void MainWindow::on_btnSVON_clicked()
{
    servostt = "1";
    StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);


}


void MainWindow::on_btnSVOFF_clicked()
{
    servostt = "0";
    StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

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
    else
        QMessageBox::critical(this, "Notice", "Please Choose Coordinate");

}

void MainWindow::on_btnSpeed_low_clicked()
{
    speed = "1";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);

}


void MainWindow::on_btnSpeed_med_clicked()
{
    speed = "2";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnSpeed_high_clicked()
{
    speed = "3";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}


void MainWindow::on_btnSpeed_top_clicked()
{
    speed = "4";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}

// PROGRAM TAB

void MainWindow::on_btnSendProg_clicked()
{
    nodeid = ChooseRobot(robotnum);
    strCurJobName = ui->lnEProgName->displayText();
    int curline = 1;
    filepath = "D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Compile/"+strCurJobName+"/"+strCurJobName+".ASM";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
//        ui->lnECmd->setText("File not found");
        QMessageBox::critical(this, "Caution", "The file is not exist");
        return;
    }


    if (inputFile.open(QIODevice::ReadOnly))
    {
        char *chPackData;

//       QString linecnt = QString::number(line_count);
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          int nosend = 0;
          QString line = in.readLine();
          QString curlin= QString::number(curline);
          StrPacketData = QString("%1ASMW,%2,%3%4").arg(STX,line,curlin,ETX);
          chPacketData = PackData(StrPacketData);
          set_str_to_variant(myVariant,chPacketData);
          UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
          QThread::msleep(50); // wait for sending command
          QString chstrPacketData = checksend(StrPacketData);
          int ncheck = checkprogsend(chstrPacketData); // a function that check if command is sent
          while (ncheck != 1 && nosend < 10)
          {
              UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
              nosend++;
          }
          if (nosend == 10)
          {
              QMessageBox::critical(this, "Caution", "Send Taught Points Fail!!!");
              return;
          }
          else
              curline++;


       }

       inputFile.close();
       QMessageBox::information(this, "Information", "Send Program OK!");
    }
    else
    {
        ui->lnECmd->setText("Error String");

    }
}

void MainWindow::on_btnSendPoints_clicked()
{
     // limit number of times resending cmd
    nodeid = ChooseRobot(robotnum);
    int curline = 1;
    filepath = "D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Compile/data.SPT";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
//        ui->lnECmd->setText("File not found");
        QMessageBox::critical(this, "Caution", "The file is not exist");
        return;
    }
    if (inputFile.open(QIODevice::ReadOnly))
    {
        char *chPackData;


       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          int nosend = 0;
          QString line = in.readLine();
          line.chop(1);
          QString curlin= QString::number(curline);
          StrPacketData = QString("%1TPTS,%2,%3%4").arg(STX,line,curlin,ETX);
          chPacketData = PackData(StrPacketData);
          set_str_to_variant(myVariant,chPacketData);
          UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
          QThread::msleep(50); // wait for sending command
          QString chstrPacketData = checksend(StrPacketData);
          int ncheck = checkprogsend(chstrPacketData); // a function that check if command is sent
          while (ncheck != 1 && nosend < 10)
          {
              UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
              nosend++;
          }
          if (nosend == 10)
          {
              QMessageBox::critical(this, "Caution", "Send Taught Points Fail!!!");
              return;
          }
          else
              curline++;
       }
       inputFile.close();
       QMessageBox::information(this, "Information", "Send Taught Points OK!");
    }
    else
    {
//        ui->lnECmd->setText("Error String");
        QMessageBox::critical(this, "Caution", "The file is not exist");

    }

}



void MainWindow::on_btnWriteProg_clicked()
{
    QProcess *process = new QProcess(this);
//    QString file = QDir::homepath + "/file.exe";
    QString file = "D:/Study/NCKH/5_SIMULATION/Geist-master/build-Geist-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/Geist.exe" ;
    process->start(file);


}

void MainWindow::on_btnCompProg_clicked()
{
    strCurJobName = ui->lnEProgName->displayText();

    QProcess* pCompileProcess = new QProcess(this);
//    pCompileProcess -> setWorkingDirectory("./Interpreter");
    pCompileProcess -> setWorkingDirectory("D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Interpreter");
//    pCompileProcess -> setWorkingDirectory("./Interpreter");
    QString strCommand = "D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Interpreter/EMC_COMPILER.exe";
    QStringList strListArg;
    strListArg << "4" << strCurJobName + ".SPT";
//    strListArg << "test.SPT";

//    pCompileProcess -> start(strCommand, strListArg);
    pCompileProcess -> start(strCommand, strListArg);
    QThread::msleep(100);
    filepath = "D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Compile/"+strCurJobName+"/"+strCurJobName+".ASM";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
        QMessageBox::critical(this, "Caution", "Compile NG");
        return;
    }
    else
        QMessageBox::information(this, "Information", "Compile OK");

}

// CHOOSE ROBOT

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "SCARA")
    {
        robotnum = 1;
        ui->tabJPointList_1->show();
        ui->tabJPointList_2->hide();
        ui->tabJPointList_3->hide();
        ui->tabJPointList_4->hide();

        ui->tabWPointList_1->show();
        ui->tabWPointList_2->hide();
        ui->tabWPointList_3->hide();
        ui->tabWPointList_4->hide();
    }

    else if (arg1 == "DELTA1")
    {
        robotnum = 2;
        ui->tabJPointList_2->show();
        ui->tabJPointList_1->hide();
        ui->tabJPointList_3->hide();
        ui->tabJPointList_4->hide();

        ui->tabWPointList_2->show();
        ui->tabWPointList_1->hide();
        ui->tabWPointList_3->hide();
        ui->tabWPointList_4->hide();
    }

    else if (arg1 == "MANIPULATOR")
    {
        robotnum = 4;
        ui->tabJPointList_4->show();
        ui->tabJPointList_1->hide();
        ui->tabJPointList_2->hide();
        ui->tabJPointList_3->hide();

        ui->tabWPointList_4->show();
        ui->tabWPointList_1->hide();
        ui->tabWPointList_2->hide();
        ui->tabWPointList_3->hide();
    }
    else
        QMessageBox::critical(this, "Notice", "Please Choose Robot to control");

}




void MainWindow::on_btnDataAdd_clicked()
{
    if (robotnum == 1)
    {

        for (int j=0; j<ui->tabJPointList_1->columnCount();j++)
        {
            jpoint  = new QTableWidgetItem;
            wpoint  = new QTableWidgetItem;

            if (j==0)
            {
                jpoint->setText(QString::number(pointlist[1]));
                wpoint->setText(QString::number(pointlist[1]));
            }
            if (j==1)
            {
                jpoint->setText(ui->lnERecv_theta1->text());
                wpoint->setText(ui->lnERecv_x->text());
            }
            if (j==2)
            {
                jpoint->setText(ui->lnERecv_theta2->text());
                wpoint->setText(ui->lnERecv_y->text());
            }
            if (j==3)
            {
                jpoint->setText(ui->lnERecv_d3->text());
                wpoint->setText(ui->lnERecv_z->text());
            }
            if (j==4)
            {
                jpoint->setText(ui->lnERecv_theta4->text());
                wpoint->setText(ui->lnERecv_roll->text());
            }
            if (j==5)
            {
                wpoint->setText(ui->lnERecv_pitch->text());
            }
            if (j==6)
            {
                wpoint->setText(ui->lnERecv_yaw->text());
            }


             ui->tabJPointList_1->setItem(pointlist[1],j,jpoint);
             ui->tabWPointList_1->setItem(pointlist[1],j,wpoint);

        }
        pointlist[1]++;
    }
    else if (robotnum == 2)
    {

        for (int j=0; j<ui->tabJPointList_2->columnCount();j++)
        {
            jpoint  = new QTableWidgetItem;
            wpoint  = new QTableWidgetItem;

            if (j==0)
            {
                jpoint->setText(QString::number(pointlist[2]));
                wpoint->setText(QString::number(pointlist[2]));
            }

            if (j==1)
            {
                jpoint->setText(ui->lnERecv_theta1_1->text());
                wpoint->setText(ui->lnERecv_x1->text());
            }
            if (j==2)
            {
                jpoint->setText(ui->lnERecv_theta2_1->text());
                wpoint->setText(ui->lnERecv_y1->text());
            }
            if (j==3)
            {
                jpoint->setText(ui->lnERecv_theta3_1->text());
                wpoint->setText(ui->lnERecv_z1->text());
            }
            if (j==4)
            {
                wpoint->setText(ui->lnERecv_roll1->text());
            }
            if (j==5)
            {
                wpoint->setText(ui->lnERecv_pitch1->text());
            }
            if (j==6)
            {
                wpoint->setText(ui->lnERecv_yaw1->text());
            }

             ui->tabJPointList_2->setItem(pointlist[2],j,jpoint);
             ui->tabWPointList_2->setItem(pointlist[2],j,wpoint);

        }
        pointlist[2]++;
    }
    else if (robotnum == 4)
    {

        for (int j=0; j<ui->tabJPointList_4->columnCount();j++)
        {
            jpoint  = new QTableWidgetItem;
            wpoint  = new QTableWidgetItem;


            if (j==0)
            {
                jpoint->setText(QString::number(pointlist[4]));
                wpoint->setText(QString::number(pointlist[4]));
            }
            if (j==1)
            {
                jpoint->setText(ui->lnERecv_J1->text());
                wpoint->setText(ui->lnERecv_x3->text());
            }
            if (j==2)
            {
                jpoint->setText(ui->lnERecv_J2->text());
                wpoint->setText(ui->lnERecv_y3->text());
            }
            if (j==3)
            {
                jpoint->setText(ui->lnERecv_J3->text());
                wpoint->setText(ui->lnERecv_z3->text());
            }
            if (j==4)
            {
                jpoint->setText(ui->lnERecv_J4->text());
                wpoint->setText(ui->lnERecv_roll3->text());
            }
            if (j==5)
            {
                jpoint->setText(ui->lnERecv_J5->text());
                wpoint->setText(ui->lnERecv_pitch3->text());
            }
            if (j==6)
            {
                jpoint->setText(ui->lnERecv_J6->text());
                wpoint->setText(ui->lnERecv_yaw3->text());
            }

             ui->tabJPointList_4->setItem(pointlist[4],j,jpoint);
             ui->tabWPointList_4->setItem(pointlist[4],j,wpoint);

        }
        pointlist[4]++;
    }


}










void MainWindow::on_tabJPointList_1_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "D:/Study/NCKH/5_SIMULATION/opcuaqt/qtopcua/debug/Compile/data.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabJPointList_1->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             ui->lnECmd->setText(str);
             //
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }

}


void MainWindow::closeEvent(QCloseEvent *e)
{
    QString close_event = ui->lbSttMsg->text();
    if (close_event == "Logging Started and Connected to OPC Server")
    {
        ClientConnect(0);
        QMainWindow::closeEvent(e);
    }
    else
    QMainWindow::closeEvent(e);
}


