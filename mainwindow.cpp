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
double dtheta3;
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
QString strPtsfilename;
QString filepath;
int svtimout;
bool svstatusmsg;
int nDIgroup;
int nDIbit;

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

UA_EndpointDescription* endpointArray = NULL;
size_t endpointArraySize = 0;
UA_StatusCode retval;

UA_Int32 noclient;

int noclientpre;

QString alarmpath = "./alarmmsg.txt";
QFile alarmfile(alarmpath);
bool balmsg = false; // check if alarmmsg opened

QString strDeltaName;

const char* cSvaddress;
QString qSvaddress;
QString svIPadd;




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


// check program checksum receiving from RC
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

void SendDI(UA_Client *client, int nbit, bool bstt)
{
    QString DIbit = QString::number(nbit);
    QString DIstt = QString::number(bstt);
    StrPacketData = QString("%1RBDI,%2,%3%4").arg(STX,DIbit,DIstt,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}



//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1-8
    ui->btnDI0->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI0->setCheckable(true);
    ui->btnDI1->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI1->setCheckable(true);
    ui->btnDI2->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI2->setCheckable(true);
    ui->btnDI3->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI3->setCheckable(true);
    ui->btnDI4->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI4->setCheckable(true);
    ui->btnDI5->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI5->setCheckable(true);
    ui->btnDI6->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI6->setCheckable(true);
    ui->btnDI7->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI7->setCheckable(true);
    //9-16
    ui->btnDI8->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI8->setCheckable(true);
    ui->btnDI9->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI9->setCheckable(true);
    ui->btnDI10->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI10->setCheckable(true);
    ui->btnDI11->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI11->setCheckable(true);
    ui->btnDI12->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI12->setCheckable(true);
    ui->btnDI13->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI13->setCheckable(true);
    ui->btnDI14->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI14->setCheckable(true);
    ui->btnDI15->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI15->setCheckable(true);
    //17-24
    ui->btnDI16->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI16->setCheckable(true);
    ui->btnDI17->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI17->setCheckable(true);
    ui->btnDI18->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI18->setCheckable(true);
    ui->btnDI19->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI19->setCheckable(true);
    ui->btnDI20->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI20->setCheckable(true);
    ui->btnDI21->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI21->setCheckable(true);
    ui->btnDI22->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI22->setCheckable(true);
    ui->btnDI23->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI23->setCheckable(true);
    //25-32
    ui->btnDI24->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI24->setCheckable(true);
    ui->btnDI25->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI25->setCheckable(true);
    ui->btnDI26->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI26->setCheckable(true);
    ui->btnDI27->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI27->setCheckable(true);
    ui->btnDI28->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI28->setCheckable(true);
    ui->btnDI29->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI29->setCheckable(true);
    ui->btnDI30->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI30->setCheckable(true);
    ui->btnDI31->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI31->setCheckable(true);
    //33-40
    ui->btnDI32->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI32->setCheckable(true);
    ui->btnDI33->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI33->setCheckable(true);
    ui->btnDI34->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI34->setCheckable(true);
    ui->btnDI35->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI35->setCheckable(true);
    ui->btnDI36->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI36->setCheckable(true);
    ui->btnDI37->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI37->setCheckable(true);
    ui->btnDI38->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI38->setCheckable(true);
    ui->btnDI39->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI39->setCheckable(true);
    //41-48
    ui->btnDI40->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI40->setCheckable(true);
    ui->btnDI41->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI41->setCheckable(true);
    ui->btnDI42->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI42->setCheckable(true);
    ui->btnDI43->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI43->setCheckable(true);
    ui->btnDI44->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI44->setCheckable(true);
    ui->btnDI45->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI45->setCheckable(true);
    ui->btnDI46->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI46->setCheckable(true);
    ui->btnDI47->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI47->setCheckable(true);
    //49-56
    ui->btnDI48->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI48->setCheckable(true);
    ui->btnDI49->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI49->setCheckable(true);
    ui->btnDI50->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI50->setCheckable(true);
    ui->btnDI51->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI51->setCheckable(true);
    ui->btnDI52->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI52->setCheckable(true);
    ui->btnDI53->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI53->setCheckable(true);
    ui->btnDI54->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI54->setCheckable(true);
    ui->btnDI55->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI55->setCheckable(true);
    //57-64
    ui->btnDI56->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI56->setCheckable(true);
    ui->btnDI57->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI57->setCheckable(true);
    ui->btnDI58->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI58->setCheckable(true);
    ui->btnDI59->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI59->setCheckable(true);
    ui->btnDI60->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI60->setCheckable(true);
    ui->btnDI61->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI61->setCheckable(true);
    ui->btnDI62->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI62->setCheckable(true);
    ui->btnDI63->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI63->setCheckable(true);
    //65-72
    ui->btnDI64->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI64->setCheckable(true);
    ui->btnDI65->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI65->setCheckable(true);
    ui->btnDI66->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI66->setCheckable(true);
    ui->btnDI67->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI67->setCheckable(true);
    ui->btnDI68->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI68->setCheckable(true);
    ui->btnDI69->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI69->setCheckable(true);
    ui->btnDI70->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI70->setCheckable(true);
    ui->btnDI71->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI71->setCheckable(true);
    //73-80
    ui->btnDI72->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI72->setCheckable(true);
    ui->btnDI73->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI73->setCheckable(true);
    ui->btnDI74->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI74->setCheckable(true);
    ui->btnDI75->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI75->setCheckable(true);
    ui->btnDI76->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI76->setCheckable(true);
    ui->btnDI77->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI77->setCheckable(true);
    ui->btnDI78->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI78->setCheckable(true);
    ui->btnDI79->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    ui->btnDI79->setCheckable(true);

    // Display status of IO
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    QMessageBox::information(this, "Information", " Enter the Server IP Adress",
                                                            QMessageBox::Ok);

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
//        UA_Client_connect(client, "opc.tcp://localhost:4880");  //connect to server
//        UA_Client_connect(client, "opc.tcp://localhost:4880");
        QByteArray ba = qSvaddress.toLocal8Bit();
        const char *c_str = ba.data();
        cSvaddress = c_str;
//        qDebug() << cSvaddress;
        UA_Client_connect(client, cSvaddress);


        UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
        noclient = *(UA_Int32*)value.data ;
        noclient += 1;
        UA_Variant_setScalarCopy(myVariant, &noclient, &UA_TYPES[UA_TYPES_INT32]);
        UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), myVariant);
        noclientpre = noclient;




        //Create update timer
        updatetimer = new QTimer(this);
        connect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        updatetimer->start(10);

        svlifetime = new QTimer(this);
        connect(svlifetime, SIGNAL(timeout()),this,SLOT(ServerTimeout()));
        svlifetime->start(500);
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
    ReadDeltaData(client);
    Alarm(client);
}

void MainWindow::Clock()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->lnETime->setText(time_text);
}

void MainWindow::ServerTimeout()
{
    nodeid = ChooseRobot(robotnum);
    QString line;
    filepath = "D:/Study/NCKH/5_SIMULATION/opcuanewserver/newopcserver/checkserver.txt";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
//        ui->lnECmd->setText("File not found");
        QMessageBox::critical(this, "Caution", "The file is not exist");
        return;
    }
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
           line = in.readLine();
       }
       if (line == "Server is off")
       {
           svstatusmsg = false;
           UA_Variant_setScalarCopy(myVariant, &svstatusmsg, &UA_TYPES[UA_TYPES_BOOLEAN]);
           UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/StatusMsg"), myVariant);
           disconnect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
           UA_Client_disconnect(client);
       }
       else if (line == "Server is on")
       {
           client = UA_Client_new();
           UA_ClientConfig_setDefault(UA_Client_getConfig(client));
//           UA_Client_connect(client, "opc.tcp://localhost:4880");
           QByteArray baa = qSvaddress.toLocal8Bit();
           const char *c_str2 = baa.data();
           cSvaddress = c_str2;

           UA_Client_connect(client, cSvaddress);
           connect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
           updatetimer->start(10);

           UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
           noclient = *(UA_Int32*)value.data;
           noclient += 1;
           if (noclient == noclientpre)
           {
               UA_Variant_setScalarCopy(myVariant, &noclient, &UA_TYPES[UA_TYPES_INT32]);
               UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), myVariant);
               svstatusmsg = true;
               UA_Variant_setScalarCopy(myVariant, &svstatusmsg, &UA_TYPES[UA_TYPES_BOOLEAN]);
               UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/StatusMsg"), myVariant);
           }
       }
       else if (line == "Server is already on")
           return;
    }

}


void MainWindow::ReadData(UA_Client *client) // SCARA Data
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

    // SCARA Data
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
}

void MainWindow::Alarm(UA_Client *client)
{

    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/AlarmMsg"), &value);
    sName = get_str_to_variant(&value);
    len = getlength(&value);
    QString strAlarm = QString::fromStdString(sName);
    strAlarm.resize(len);

}

void MainWindow::ReadDeltaData(UA_Client *client)
{
    //DELTA 1
    //theta1
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta1"), &value);
    dtheta1 = *(UA_Double*)value.data ;
    QString DTtheta1 = QString::number(dtheta1);
    ui->lnERecv_theta1_1->setText(DTtheta1);
    //theta2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta2"), &value);
    dtheta2 = *(UA_Double*)value.data ;
    QString DTtheta2 = QString::number(dtheta2);
    ui->lnERecv_theta2_1->setText(DTtheta2);
    //theta3
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta2"), &value);
    dtheta3 = *(UA_Double*)value.data ;
    QString DTtheta3 = QString::number(dtheta3);
    ui->lnERecv_theta3_1->setText(DTtheta3);

    // DELTA 2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta1"), &value);
    dtheta1 = *(UA_Double*)value.data ;
    DTtheta1 = QString::number(dtheta1);
    ui->lnERecv_theta1_1->setText(DTtheta1);
    //theta2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta2"), &value);
    dtheta2 = *(UA_Double*)value.data ;
    DTtheta2 = QString::number(dtheta2);
    ui->lnERecv_theta2_1->setText(DTtheta2);
    //theta3
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot2/theta2"), &value);
    dtheta3 = *(UA_Double*)value.data ;
    DTtheta3 = QString::number(dtheta3);
    ui->lnERecv_theta3_1->setText(DTtheta3);

    // DELTA 3
}

// SERVER IP ADDRESS
void MainWindow::on_btnSaveIP_clicked()
{
    svIPadd = ui->lnEServerIP->text();
    qSvaddress = "opc.tcp://"+svIPadd+":4880";

}


// CONNECTION

void MainWindow::on_btnStart_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Information", "1. Check the server status!!!\n"
                                                                                 "2. Choose the robot to control",
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

    else if (arg1 == "DELTA2")
    {
        robotnum = 3;
        ui->tabJPointList_3->show();
        ui->tabJPointList_1->hide();
        ui->tabJPointList_2->hide();
        ui->tabJPointList_4->hide();

        ui->tabWPointList_3->show();
        ui->tabWPointList_1->hide();
        ui->tabWPointList_2->hide();
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

// JOG TAB

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
    filepath = "./debug/Compile/"+strCurJobName+"/"+strCurJobName+".ASM";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
//        ui->lnECmd->setText("File not found");
        QMessageBox::critical(this, "Caution", "The file is not exist");
        return;
    }


    if (inputFile.open(QIODevice::ReadOnly))
    {
//        char *chPackData;

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
    strPtsfilename = ui->lnEDataPts->displayText();
    filepath = "./DataPoints/"+strPtsfilename+".SPT";
    QFile inputFile(filepath);
    if(!inputFile.exists())
    {
//        ui->lnECmd->setText("File not found");
        QMessageBox::critical(this, "Caution", "The file is not exist");
        return;
    }
    if (inputFile.open(QIODevice::ReadOnly))
    {
//        char *chPackData;


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
          int ncheck = checkprogsend(chstrPacketData); // function that check if command is sent
          while (ncheck != 1 && nosend < 10)
          {
              UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
              nosend++;
          }
          if (nosend == 10)
          {
              QMessageBox::critical(this, "Caution", "Send Taught Points Failed!!!");
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
    else if (robotnum == 3)
    {

        for (int j=0; j<ui->tabJPointList_3->columnCount();j++)
        {
            jpoint  = new QTableWidgetItem;
            wpoint  = new QTableWidgetItem;

            if (j==0)
            {
                jpoint->setText(QString::number(pointlist[3]));
                wpoint->setText(QString::number(pointlist[3]));
            }

            if (j==1)
            {
                jpoint->setText(ui->lnERecv_theta1_2->text());
                wpoint->setText(ui->lnERecv_x2->text());
            }
            if (j==2)
            {
                jpoint->setText(ui->lnERecv_theta2_2->text());
                wpoint->setText(ui->lnERecv_y2->text());
            }
            if (j==3)
            {
                jpoint->setText(ui->lnERecv_theta3_2->text());
                wpoint->setText(ui->lnERecv_z2->text());
            }
            if (j==4)
            {
                wpoint->setText(ui->lnERecv_roll2->text());
            }
            if (j==5)
            {
                wpoint->setText(ui->lnERecv_pitch2->text());
            }
            if (j==6)
            {
                wpoint->setText(ui->lnERecv_yaw2->text());
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


void MainWindow::on_btnDataDel_clicked()
{
    if (robotnum == 1)
    {
        ui->tabJPointList_1->clear();
        ui->tabWPointList_1->clear();
    }
    else if (robotnum == 2)
    {
        ui->tabJPointList_2->clear();
        ui->tabWPointList_2->clear();
    }
    else if (robotnum == 3)
    {
        ui->tabJPointList_3->clear();
        ui->tabWPointList_3->clear();
    }
    else if (robotnum == 4)
    {
        ui->tabJPointList_4->clear();
        ui->tabWPointList_4->clear();
    }
}

void MainWindow::on_btnOpenPts_clicked()
{

    QProcess *process = new QProcess(this);
//    QString file = QDir::homepath + "/file.exe";
    QString file = "D:/Study/NCKH/5_SIMULATION/Geist-master/build-Geist-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/Geist.exe" ;
    process->start(file);

}


// DATA TAB

// Data Point Joint List
void MainWindow::on_tabJPointList_1_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataJ1.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabJPointList_1->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}

void MainWindow::on_tabJPointList_2_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataJ2.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabJPointList_2->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}

void MainWindow::on_tabJPointList_3_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataJ3.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabJPointList_3->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}


void MainWindow::on_tabJPointList_4_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataJ4.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabJPointList_4->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}

// Data Point World List
void MainWindow::on_tabWPointList_1_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataW1.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabWPointList_1->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}

void MainWindow::on_tabWPointList_2_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataW2.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabWPointList_2->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}


void MainWindow::on_tabWPointList_3_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataW3.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabWPointList_3->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
             if (str != NULL)
             {
                 stream << str << ",";
             }
         }
         stream << endl;
    }
}


void MainWindow::on_tabWPointList_4_itemClicked(QTableWidgetItem *item)
{
    int nrow = item->row();
    filepath = "./DataPoints/dataW4.SPT";
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
         QTextStream stream(&file);
         for (int j=0; j<7;j++)
         {
             getpoint = new QTableWidgetItem;
             getpoint = ui->tabWPointList_4->item(nrow,j);
             QString str = getpoint->data(Qt::DisplayRole).toString();
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











// IO TAB

//1-8
void MainWindow::on_btnDI7_toggled(bool checked)
{
    nDIbit = 7;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI7->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI7->setChecked(false);
        ui->btnDI7->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI6_toggled(bool checked)
{
    nDIbit = 6;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI6->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI6->setChecked(false);
        ui->btnDI6->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);

}


void MainWindow::on_btnDI5_toggled(bool checked)
{
    nDIbit = 5;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI5->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI5->setChecked(false);
        ui->btnDI5->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI4_toggled(bool checked)
{
    nDIbit = 4;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI4->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI4->setChecked(false);
        ui->btnDI4->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI3_toggled(bool checked)
{
    nDIbit = 3;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI3->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI3->setChecked(false);
        ui->btnDI3->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);

}


void MainWindow::on_btnDI2_toggled(bool checked)
{
    nDIbit = 2;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI2->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI2->setChecked(false);
        ui->btnDI2->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI1_toggled(bool checked)
{
    nDIbit = 1;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI1->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI1->setChecked(false);
        ui->btnDI1->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
     SendDI(client,nDIbit,checked);

}


void MainWindow::on_btnDI0_toggled(bool checked)
{
    nDIbit = 0;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 1))
    {
        ui->btnDI0->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI0->setChecked(false);
        ui->btnDI0->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 1)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);

}

//9-16
void MainWindow::on_btnDI15_toggled(bool checked)
{
    nDIbit = 15;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI15->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI15->setChecked(false);
        ui->btnDI15->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);

}


void MainWindow::on_btnDI14_toggled(bool checked)
{
    nDIbit = 14;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI14->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI14->setChecked(false);
        ui->btnDI14->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);

}


void MainWindow::on_btnDI13_toggled(bool checked)
{
    nDIbit = 13;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI13->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI13->setChecked(false);
        ui->btnDI13->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI12_toggled(bool checked)
{
    nDIbit = 12;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI12->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI12->setChecked(false);
        ui->btnDI12->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI11_toggled(bool checked)
{
    nDIbit = 11;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI11->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI11->setChecked(false);
        ui->btnDI11->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI10_toggled(bool checked)
{
    nDIbit = 10;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI10->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI10->setChecked(false);
        ui->btnDI10->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI9_toggled(bool checked)
{
    nDIbit = 9;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI9->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI9->setChecked(false);
        ui->btnDI9->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI8_toggled(bool checked)
{
    nDIbit = 8;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 2))
    {
        ui->btnDI8->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI8->setChecked(false);
        ui->btnDI8->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 2)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//17-24
void MainWindow::on_btnDI23_toggled(bool checked)
{
    nDIbit = 23;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI23->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI23->setChecked(false);
        ui->btnDI23->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI22_toggled(bool checked)
{
    nDIbit = 22;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI22->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI22->setChecked(false);
        ui->btnDI22->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI21_toggled(bool checked)
{
    nDIbit = 21;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI21->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI21->setChecked(false);
        ui->btnDI21->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI20_toggled(bool checked)
{
    nDIbit = 20;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI20->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI20->setChecked(false);
        ui->btnDI20->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI19_toggled(bool checked)
{
    nDIbit = 19;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI19->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI19->setChecked(false);
        ui->btnDI19->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI18_toggled(bool checked)
{
    nDIbit = 18;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI18->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI18->setChecked(false);
        ui->btnDI18->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI17_toggled(bool checked)
{
    nDIbit = 17;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI17->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI17->setChecked(false);
        ui->btnDI17->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI16_toggled(bool checked)
{
    nDIbit = 16;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 3))
    {
        ui->btnDI16->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI16->setChecked(false);
        ui->btnDI16->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 3)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//25-32
void MainWindow::on_btnDI31_toggled(bool checked)
{
    nDIbit = 31;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI31->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI31->setChecked(false);
        ui->btnDI31->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI30_toggled(bool checked)
{
    nDIbit = 30;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI30->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI30->setChecked(false);
        ui->btnDI30->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI29_toggled(bool checked)
{
    nDIbit = 29;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI29->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI29->setChecked(false);
        ui->btnDI29->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI28_toggled(bool checked)
{
    nDIbit = 28;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI28->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI28->setChecked(false);
        ui->btnDI28->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI27_toggled(bool checked)
{
    nDIbit = 27;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI27->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI27->setChecked(false);
        ui->btnDI27->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI26_toggled(bool checked)
{
    nDIbit = 26;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI26->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI26->setChecked(false);
        ui->btnDI26->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI25_toggled(bool checked)
{
    nDIbit = 25;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI25->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI25->setChecked(false);
        ui->btnDI25->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI24_toggled(bool checked)
{
    nDIbit = 24;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 4))
    {
        ui->btnDI24->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI24->setChecked(false);
        ui->btnDI24->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 4)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//33-40
void MainWindow::on_btnDI39_toggled(bool checked)
{
    nDIbit = 39;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI39->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI39->setChecked(false);
        ui->btnDI39->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI38_toggled(bool checked)
{
    nDIbit = 38;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI38->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI38->setChecked(false);
        ui->btnDI38->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI37_toggled(bool checked)
{
    nDIbit = 37;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI37->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI37->setChecked(false);
        ui->btnDI37->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI36_toggled(bool checked)
{
    nDIbit = 36;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI36->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI36->setChecked(false);
        ui->btnDI36->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI35_toggled(bool checked)
{
    nDIbit = 35;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI35->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI35->setChecked(false);
        ui->btnDI35->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI34_toggled(bool checked)
{
    nDIbit = 34;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI34->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI34->setChecked(false);
        ui->btnDI34->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI33_toggled(bool checked)
{
    nDIbit = 33;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI33->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI33->setChecked(false);
        ui->btnDI33->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI32_toggled(bool checked)
{
    nDIbit = 32;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 5))
    {
        ui->btnDI32->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI32->setChecked(false);
        ui->btnDI32->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 5)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//41-48
void MainWindow::on_btnDI47_toggled(bool checked)
{
    nDIbit = 47;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI47->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI47->setChecked(false);
        ui->btnDI47->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI46_toggled(bool checked)
{
    nDIbit = 46;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI46->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI46->setChecked(false);
        ui->btnDI46->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI45_toggled(bool checked)
{
    nDIbit = 45;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI45->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI45->setChecked(false);
        ui->btnDI45->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI44_toggled(bool checked)
{
    nDIbit = 44;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI44->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI44->setChecked(false);
        ui->btnDI44->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI43_toggled(bool checked)
{
    nDIbit = 43;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI43->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI43->setChecked(false);
        ui->btnDI43->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI42_toggled(bool checked)
{
    nDIbit = 42;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI42->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI42->setChecked(false);
        ui->btnDI42->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI41_toggled(bool checked)
{
    nDIbit = 41;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI41->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI41->setChecked(false);
        ui->btnDI41->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI40_toggled(bool checked)
{
    nDIbit = 40;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 6))
    {
        ui->btnDI40->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI40->setChecked(false);
        ui->btnDI40->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 6)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//49-56
void MainWindow::on_btnDI55_toggled(bool checked)
{
    nDIbit = 55;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI55->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI55->setChecked(false);
        ui->btnDI55->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI54_toggled(bool checked)
{
    nDIbit = 54;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI54->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI54->setChecked(false);
        ui->btnDI54->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI53_toggled(bool checked)
{
    nDIbit = 53;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI53->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI53->setChecked(false);
        ui->btnDI53->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI52_toggled(bool checked)
{
    nDIbit = 52;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI52->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI52->setChecked(false);
        ui->btnDI52->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI51_toggled(bool checked)
{
    nDIbit = 51;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI51->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI51->setChecked(false);
        ui->btnDI51->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI50_toggled(bool checked)
{
    nDIbit = 50;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI50->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI50->setChecked(false);
        ui->btnDI50->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI49_toggled(bool checked)
{
    nDIbit = 49;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI49->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI49->setChecked(false);
        ui->btnDI49->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI48_toggled(bool checked)
{
    nDIbit = 48;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 7))
    {
        ui->btnDI48->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI48->setChecked(false);
        ui->btnDI48->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 7)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//57-64
void MainWindow::on_btnDI63_toggled(bool checked)
{
    nDIbit = 63;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI63->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI63->setChecked(false);
        ui->btnDI63->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI62_toggled(bool checked)
{
    nDIbit = 62;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI62->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI62->setChecked(false);
        ui->btnDI62->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI61_toggled(bool checked)
{
    nDIbit = 61;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI61->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI61->setChecked(false);
        ui->btnDI61->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI60_toggled(bool checked)
{
    nDIbit = 60;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI60->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI60->setChecked(false);
        ui->btnDI60->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI59_toggled(bool checked)
{
    nDIbit = 59;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI59->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI59->setChecked(false);
        ui->btnDI59->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI58_toggled(bool checked)
{
    nDIbit = 58;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI58->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI58->setChecked(false);
        ui->btnDI58->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI57_toggled(bool checked)
{
    nDIbit = 57;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI57->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI57->setChecked(false);
        ui->btnDI57->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI56_toggled(bool checked)
{
    nDIbit = 56;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 8))
    {
        ui->btnDI56->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI56->setChecked(false);
        ui->btnDI56->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 8)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//65-72
void MainWindow::on_btnDI71_toggled(bool checked)
{
    nDIbit = 71;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI71->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI71->setChecked(false);
        ui->btnDI71->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI70_toggled(bool checked)
{
    nDIbit = 70;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI70->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI70->setChecked(false);
        ui->btnDI70->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI69_toggled(bool checked)
{
    nDIbit = 69;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI69->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI69->setChecked(false);
        ui->btnDI69->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI68_toggled(bool checked)
{
    nDIbit = 68;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI68->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI68->setChecked(false);
        ui->btnDI68->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI67_toggled(bool checked)
{
    nDIbit = 67;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI67->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI67->setChecked(false);
        ui->btnDI67->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI66_toggled(bool checked)
{
    nDIbit = 66;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI66->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI66->setChecked(false);
        ui->btnDI66->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI65_toggled(bool checked)
{
    nDIbit = 65;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI65->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI65->setChecked(false);
        ui->btnDI65->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI64_toggled(bool checked)
{
    nDIbit = 64;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 9))
    {
        ui->btnDI64->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI64->setChecked(false);
        ui->btnDI64->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 9)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}

//73-80
void MainWindow::on_btnDI79_toggled(bool checked)
{
    nDIbit = 79;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI79->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI79->setChecked(false);
        ui->btnDI79->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI78_toggled(bool checked)
{
    nDIbit = 78;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI78->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI78->setChecked(false);
        ui->btnDI78->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI77_toggled(bool checked)
{
    nDIbit = 77;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI77->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI77->setChecked(false);
        ui->btnDI77->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI76_toggled(bool checked)
{
    nDIbit = 76;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI76->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI76->setChecked(false);
        ui->btnDI76->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI75_toggled(bool checked)
{
    nDIbit = 75;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI75->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI75->setChecked(false);
        ui->btnDI75->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI74_toggled(bool checked)
{
    nDIbit = 74;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI74->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI74->setChecked(false);
        ui->btnDI74->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI73_toggled(bool checked)
{
    nDIbit = 73;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI73->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI73->setChecked(false);
        ui->btnDI73->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}


void MainWindow::on_btnDI72_toggled(bool checked)
{
    nDIbit = 72;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (checked && (nDIgroup == 10))
    {
        ui->btnDI72->setIcon(QIcon("./IOpics/Green pilot light 2.png"));
        ui->lbDIStt0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    else
    {
        ui->btnDI72->setChecked(false);
        ui->btnDI72->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        if (nDIgroup == 10)
            ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    SendDI(client,nDIbit,checked);
}




//DI groups
void MainWindow::on_chbDIgr1_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 1;

        ui->lnEDIgr->setText("01");
        ui->lnEDIinput->setText("1-8");
        ui->lnEDIin1->setText("01");
        ui->lnEDIin2->setText("02");
        ui->lnEDIin3->setText("03");
        ui->lnEDIin4->setText("04");
        ui->lnEDIin5->setText("05");
        ui->lnEDIin6->setText("06");
        ui->lnEDIin7->setText("07");
        ui->lnEDIin8->setText("08");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI0->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI1->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI2->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI3->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI4->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI5->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI6->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI7->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));

    }
    ui->btnDI0->setChecked(false);
    ui->btnDI1->setChecked(false);
    ui->btnDI2->setChecked(false);
    ui->btnDI3->setChecked(false);
    ui->btnDI4->setChecked(false);
    ui->btnDI5->setChecked(false);
    ui->btnDI6->setChecked(false);
    ui->btnDI7->setChecked(false);

}


void MainWindow::on_chbDIgr2_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 2;

        ui->lnEDIgr->setText("02");
        ui->lnEDIinput->setText("9-16");
        ui->lnEDIin1->setText("9");
        ui->lnEDIin2->setText("10");
        ui->lnEDIin3->setText("11");
        ui->lnEDIin4->setText("12");
        ui->lnEDIin5->setText("13");
        ui->lnEDIin6->setText("14");
        ui->lnEDIin7->setText("15");
        ui->lnEDIin8->setText("16");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI8->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI9->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI10->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI11->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI12->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI13->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI14->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI15->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));

    }
    ui->btnDI8->setChecked(false);
    ui->btnDI9->setChecked(false);
    ui->btnDI10->setChecked(false);
    ui->btnDI11->setChecked(false);
    ui->btnDI12->setChecked(false);
    ui->btnDI13->setChecked(false);
    ui->btnDI14->setChecked(false);
    ui->btnDI15->setChecked(false);


}


void MainWindow::on_chbDIgr3_stateChanged(int arg1)
{

    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 3;

        ui->lnEDIgr->setText("03");
        ui->lnEDIinput->setText("17-24");
        ui->lnEDIin1->setText("17");
        ui->lnEDIin2->setText("18");
        ui->lnEDIin3->setText("19");
        ui->lnEDIin4->setText("20");
        ui->lnEDIin5->setText("21");
        ui->lnEDIin6->setText("22");
        ui->lnEDIin7->setText("23");
        ui->lnEDIin8->setText("24");



    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI16->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI17->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI18->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI19->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI20->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI21->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI22->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI23->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI16->setChecked(false);
    ui->btnDI17->setChecked(false);
    ui->btnDI18->setChecked(false);
    ui->btnDI19->setChecked(false);
    ui->btnDI20->setChecked(false);
    ui->btnDI21->setChecked(false);
    ui->btnDI22->setChecked(false);
    ui->btnDI23->setChecked(false);

}


void MainWindow::on_chbDIgr4_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 4;

        ui->lnEDIgr->setText("04");
        ui->lnEDIinput->setText("25-32");
        ui->lnEDIin1->setText("25");
        ui->lnEDIin2->setText("26");
        ui->lnEDIin3->setText("27");
        ui->lnEDIin4->setText("28");
        ui->lnEDIin5->setText("29");
        ui->lnEDIin6->setText("30");
        ui->lnEDIin7->setText("31");
        ui->lnEDIin8->setText("32");


    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI24->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI25->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI26->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI27->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI28->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI29->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI30->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI31->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI24->setChecked(false);
    ui->btnDI25->setChecked(false);
    ui->btnDI26->setChecked(false);
    ui->btnDI27->setChecked(false);
    ui->btnDI28->setChecked(false);
    ui->btnDI29->setChecked(false);
    ui->btnDI30->setChecked(false);
    ui->btnDI31->setChecked(false);

}


void MainWindow::on_chbDIgr5_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 5;

        ui->lnEDIgr->setText("05");
        ui->lnEDIinput->setText("33-40");
        ui->lnEDIin1->setText("33");
        ui->lnEDIin2->setText("34");
        ui->lnEDIin3->setText("35");
        ui->lnEDIin4->setText("36");
        ui->lnEDIin5->setText("37");
        ui->lnEDIin6->setText("38");
        ui->lnEDIin7->setText("39");
        ui->lnEDIin8->setText("40");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI32->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI33->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI34->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI35->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI36->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI37->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI38->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI39->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI32->setChecked(false);
    ui->btnDI33->setChecked(false);
    ui->btnDI34->setChecked(false);
    ui->btnDI35->setChecked(false);
    ui->btnDI36->setChecked(false);
    ui->btnDI37->setChecked(false);
    ui->btnDI38->setChecked(false);
    ui->btnDI39->setChecked(false);

}


void MainWindow::on_chbDIgr6_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 6;

        ui->lnEDIgr->setText("06");
        ui->lnEDIinput->setText("41-48");
        ui->lnEDIin1->setText("41");
        ui->lnEDIin2->setText("42");
        ui->lnEDIin3->setText("43");
        ui->lnEDIin4->setText("44");
        ui->lnEDIin5->setText("45");
        ui->lnEDIin6->setText("46");
        ui->lnEDIin7->setText("47");
        ui->lnEDIin8->setText("48");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI32->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI33->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI34->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI35->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI36->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI37->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI38->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI39->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI40->setChecked(false);
    ui->btnDI41->setChecked(false);
    ui->btnDI42->setChecked(false);
    ui->btnDI43->setChecked(false);
    ui->btnDI44->setChecked(false);
    ui->btnDI45->setChecked(false);
    ui->btnDI46->setChecked(false);
    ui->btnDI47->setChecked(false);
}


void MainWindow::on_chbDIgr7_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 7;

        ui->lnEDIgr->setText("07");
        ui->lnEDIinput->setText("49-56");
        ui->lnEDIin1->setText("49");
        ui->lnEDIin2->setText("50");
        ui->lnEDIin3->setText("51");
        ui->lnEDIin4->setText("52");
        ui->lnEDIin5->setText("53");
        ui->lnEDIin6->setText("54");
        ui->lnEDIin7->setText("55");
        ui->lnEDIin8->setText("56");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI48->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI49->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI50->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI51->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI52->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI53->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI54->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI55->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI48->setChecked(false);
    ui->btnDI49->setChecked(false);
    ui->btnDI50->setChecked(false);
    ui->btnDI51->setChecked(false);
    ui->btnDI52->setChecked(false);
    ui->btnDI53->setChecked(false);
    ui->btnDI54->setChecked(false);
    ui->btnDI55->setChecked(false);
}


void MainWindow::on_chbDIgr8_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr9->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 8;

        ui->lnEDIgr->setText("08");
        ui->lnEDIinput->setText("57-64");
        ui->lnEDIin1->setText("57");
        ui->lnEDIin2->setText("58");
        ui->lnEDIin3->setText("59");
        ui->lnEDIin4->setText("60");
        ui->lnEDIin5->setText("61");
        ui->lnEDIin6->setText("62");
        ui->lnEDIin7->setText("63");
        ui->lnEDIin8->setText("64");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI56->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI57->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI58->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI59->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI60->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI61->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI62->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI63->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));

    }
    ui->btnDI56->setChecked(false);
    ui->btnDI57->setChecked(false);
    ui->btnDI58->setChecked(false);
    ui->btnDI59->setChecked(false);
    ui->btnDI60->setChecked(false);
    ui->btnDI61->setChecked(false);
    ui->btnDI62->setChecked(false);
    ui->btnDI63->setChecked(false);

}


void MainWindow::on_chbDIgr9_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr10->setChecked(false);

        nDIgroup = 9;

        ui->lnEDIgr->setText("09");
        ui->lnEDIinput->setText("65-72");
        ui->lnEDIin1->setText("65");
        ui->lnEDIin2->setText("66");
        ui->lnEDIin3->setText("67");
        ui->lnEDIin4->setText("68");
        ui->lnEDIin5->setText("69");
        ui->lnEDIin6->setText("70");
        ui->lnEDIin7->setText("71");
        ui->lnEDIin8->setText("72");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI64->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI65->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI66->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI67->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI68->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI69->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI70->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI71->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI64->setChecked(false);
    ui->btnDI65->setChecked(false);
    ui->btnDI66->setChecked(false);
    ui->btnDI67->setChecked(false);
    ui->btnDI68->setChecked(false);
    ui->btnDI69->setChecked(false);
    ui->btnDI70->setChecked(false);
    ui->btnDI71->setChecked(false);

}


void MainWindow::on_chbDIgr10_stateChanged(int arg1)
{
    if (arg1)
    {

        ui->chbDIgr1->setChecked(false);
        ui->chbDIgr2->setChecked(false);
        ui->chbDIgr3->setChecked(false);
        ui->chbDIgr4->setChecked(false);
        ui->chbDIgr5->setChecked(false);
        ui->chbDIgr6->setChecked(false);
        ui->chbDIgr7->setChecked(false);
        ui->chbDIgr8->setChecked(false);
        ui->chbDIgr9->setChecked(false);

        nDIgroup = 10;

        ui->lnEDIgr->setText("10");
        ui->lnEDIinput->setText("73-80");
        ui->lnEDIin1->setText("73");
        ui->lnEDIin2->setText("74");
        ui->lnEDIin3->setText("75");
        ui->lnEDIin4->setText("76");
        ui->lnEDIin5->setText("77");
        ui->lnEDIin6->setText("78");
        ui->lnEDIin7->setText("79");
        ui->lnEDIin8->setText("80");

    }
    else
    {
        nDIgroup = 0;

        ui->lnEDIgr->clear();
        ui->lnEDIinput->clear();
        ui->lnEDIin1->clear();
        ui->lnEDIin2->clear();
        ui->lnEDIin3->clear();
        ui->lnEDIin4->clear();
        ui->lnEDIin5->clear();
        ui->lnEDIin6->clear();
        ui->lnEDIin7->clear();
        ui->lnEDIin8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDIStt0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        ui->btnDI72->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI73->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI74->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI75->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI76->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI77->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI78->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
        ui->btnDI79->setIcon(QIcon("./IOpics/Pilot light 2 (off).png"));
    }
    ui->btnDI72->setChecked(false);
    ui->btnDI73->setChecked(false);
    ui->btnDI74->setChecked(false);
    ui->btnDI75->setChecked(false);
    ui->btnDI76->setChecked(false);
    ui->btnDI77->setChecked(false);
    ui->btnDI78->setChecked(false);
    ui->btnDI79->setChecked(false);

}









