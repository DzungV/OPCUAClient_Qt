#include "mainwindow.h"
#include "open62541/types.h"
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
QString strAlarm;
QString strAlarmpre = "0";
std::string sAlarm;
byte bAlarm;
std::string strIO;
byte IOlen;
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

QTableWidgetItem *operevent;
QTableWidgetItem *alaevent;

int nopereventcnt;
int nalaeventcnt;
//jpoint = new QTableWidgetItem;

const char* nodeid;
const char* nodeidack;
const char* nodeidio;

QString strCurJobName;
QString strPtsfilename;
QString filepath;
int svtimout;
bool svstatusmsg;
int nDIgroup;
int nDOgroup;
int nDIbit;

int nDObit;
bool bToggleDO;

char* chPacketData;

QString IOsig;
int nIOarg[5];


QString STX = "2";
QString ETX = "3";

QString no_joint;
QString servostt;
QString direction;
QString coords;
QString StrPacketData;
QString speed;
QString seclevel;
QString rbMode;
QString lockRBC;

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

int ntoolnum;
int njogsp;
int ncoord;
bool bservostt;
int nsystemstt;
bool brbmode;
int nseclevel;
bool blockrbc;


bool bservosttpre;
int nsystemsttpre;
bool brbmodepre;
int nseclevelpre;
bool blockrbcpre;


bool bCMDflag;
bool bCMDcheck;

int count;

byte DIgroup1;
byte DIgroup2;
byte DOgroup1;
byte DOgroup2;

QDateTime date = QDateTime::currentDateTime();
QString formattedtime = date.toString("dd.MM.yyyy hh:mm:ss");






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
    {
        node = "ns=4;s=Robot1/CMDSend";
        nodeidack = "ns=4;s=Robot1/CMDAck";
        nodeidio = "ns=4;s=Robot1/IOSend";
    }
    else if (robot == 2)
    {
        node = "ns=4;s=Robot2/CMDSend";
        nodeidack = "ns=4;s=Robot2/CMDAck";
        nodeidio = "ns=4;s=Robot2/IOSend";
    }

    else if (robot == 3)
    {
        node = "ns=4;s=Robot3/CMDSend";
        nodeidack = "ns=4;s=Robot3/CMDAck";
        nodeidio = "ns=4;s=Robot3/IOSend";
    }


    return node;
}


// check program checksum receiving from RC
int checkprogsend (QString &strPackData)
{
    int chck = 0;
    UA_Variant value;
    UA_Client_readValueAttribute(client, UA_NODEID(nodeidack), &value);
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

// Check checksum
QString CheckCrc(QString &PacketData)
{
    int usCheckSum = 0;
    unsigned short usPacketSize;
    int i;
    char ch;


    QString find = ";";
    QString GetCrc = PacketData.left(PacketData.indexOf(find));
    GetCrc.remove(0,1);
    usPacketSize = GetCrc.length();
    std::string strGetCrc = GetCrc.toStdString() ;
    for (i = 0; i < usPacketSize; i++)
    {
        ch = strGetCrc.at(i);
        usCheckSum = usCheckSum ^ ch;
    }


    //PacketData.chop(1);
    QString strChSumSend = PacketData.mid(PacketData.indexOf(find)+1);
    strChSumSend.chop(1);
    int nChSumSend = strChSumSend.toInt();
    if (usCheckSum == nChSumSend)
    {
        return PacketData;
    }
    else
        qDebug() << "failed";
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



void SendDO(UA_Client *client, int ngroup, int nbit, bool bstt)
{
    QString DOgroup = QString::number(ngroup);
    QString DObit = QString::number(nbit);
    QString DOstt = QString::number(bstt);
    StrPacketData = QString("%1RBDO,%2,%3,%4%5").arg(STX,DOgroup,DObit,DOstt,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
}



QString Dispjogsp(int num)
{
   QString qspeed;
   if (num == 0)
       qspeed = "Low Speed";
   else if (num == 1)
       qspeed = "Medium Speed";
   else if (num == 2)
       qspeed = "High Speed";
   else if (num == 3 )
       qspeed = "Top Speed";
   return qspeed;
}

QString Dispcoord (int numm)
{
    QString qcoord;
    if (numm == 0)
        qcoord = "Joint Coordinates";
    else if (numm == 1)
        qcoord = "XYZ-World Coordinates";
    else if (numm == 2)
        qcoord = "XYZ-Tool Coordinates";
    else if (numm == 3 )
        qcoord = "XYZ-User Frame Coordinates";
    return qcoord;
}
QString Dispservostt (bool stt)
{
    QString qservo;
    if (stt)
        qservo = "ON";
    else
        qservo = "OFF";
    return qservo;
}
QString Dispsysstt (int num)
{
    QString qsysstt;
    if (num == 0)
        qsysstt = "OK Status";
    else if (num == 1)
        qsysstt = "Alarm";
//    else if (num == )
//        qsysstt = "Run";
//    else if (num == 4 )
//        qsysstt = "Pause";
    return qsysstt;
}
QString Dispmode (bool mod)
{
    QString qmode;
    if (!mod)
        qmode = "TEACH mode";
    else
        qmode = "AUTOMATIC mode";
    return qmode;
}
QString Dispseclvl (int num)
{
    QString qsec;
    if (num == 0)
        qsec = "OPERATION mode";
    else if (num == 1)
        qsec = "EDIT mode";
    else if (num == 2)
        qsec = "MANAGEMENT mode";
    return qsec;
}
QString DispRBC (bool lck)
{
    QString qlock;
    if (!lck)
        qlock = "The status of controller is unlocked";
    else
        qlock = "The status of controller is locked";
    return qlock;
}



//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // Display status of IO
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");

    // SET UP DI ICON
    ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt8->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt9->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt10->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt11->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt12->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt13->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt14->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt15->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt16->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt17->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt18->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt19->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt20->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt21->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt22->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt23->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt24->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt25->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt26->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt27->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt28->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt29->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt30->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt31->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt32->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt33->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt34->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt35->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt36->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt37->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt38->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt39->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt40->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt41->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt42->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt43->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt44->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt45->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt46->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt47->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt48->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt49->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt50->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt51->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt52->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt53->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt54->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt55->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt56->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt57->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt58->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt59->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt60->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt61->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt62->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt63->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt64->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt65->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt66->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt67->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt68->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt69->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt70->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt71->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt72->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt73->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt74->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt75->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt76->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt77->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt78->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt79->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDIStt80->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    // SET UP DO ICON
    ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    ui->lbDOStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt8->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt9->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt10->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt11->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt12->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt13->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt14->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt15->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt16->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt17->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt18->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt19->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt20->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt21->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt22->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt23->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt24->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt25->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt26->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt27->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt28->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt29->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt30->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt31->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt32->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt33->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt34->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt35->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt36->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt37->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt38->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt39->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt40->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt41->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt42->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt43->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt44->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt45->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt46->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt47->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt48->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt49->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt50->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt51->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt52->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt53->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt54->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt55->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt56->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt57->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt58->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt59->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt60->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt61->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt62->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt63->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt64->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt65->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt66->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt67->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt68->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt69->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt70->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt71->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt72->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt73->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt74->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt75->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt76->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt77->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt78->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt79->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    ui->lbDOStt80->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    //

    ui->btnDO1->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO1->setCheckable(true);
    ui->btnDO2->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO2->setCheckable(true);
    ui->btnDO3->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO3->setCheckable(true);
    ui->btnDO4->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO4->setCheckable(true);
    ui->btnDO5->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO5->setCheckable(true);
    ui->btnDO6->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO6->setCheckable(true);
    ui->btnDO7->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO7->setCheckable(true);
    ui->btnDO8->setIcon(QIcon("./IOpics/offbtn.jpg"));
    ui->btnDO8->setCheckable(true);
    //
    ui->btnRBMode->setIcon(QIcon("./IOpics/auto mode.jpg"));
    ui->btnRBMode->setCheckable(true);
    ui->btnRBCLock->setIcon(QIcon("./IOpics/lock RBC.jpg"));
    ui->btnRBCLock->setCheckable(true);
    ui->btnRBServo->setIcon(QIcon("./IOpics/servo off.jpg"));
    ui->btnRBServo->setCheckable(true);


    ui->lnEServerIP->setText("localhost");

    //set default status bar
//    ui->tab_Jog->setEnabled(false);
//    ui->btnRBMode->setEnabled(false);
//    SetSttbar(0);
//    ui->cbEnableDO->setEnabled(true);





//    QMessageBox::information(this, "Information", " Enter the Server IP Adress",
//                                                            QMessageBox::Ok);

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




        //Create update timer to read robot data
        updatetimer = new QTimer(this);
        connect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        updatetimer->start(10);

        //Create server lifetime timer to check the connection
        svlifetime = new QTimer(this);
        connect(svlifetime, SIGNAL(timeout()),this,SLOT(ServerTimeout()));
        svlifetime->start(500);

        //Create IO and Alarm timer to read IO signals and Alarm messages
        IOAlarmtimer = new QTimer(this);
        connect(IOAlarmtimer, SIGNAL(timeout()),this,SLOT(IOAlarmTick()));
        IOAlarmtimer->start(50);


    }
    else if (status==0)
    {
        disconnect(updatetimer, SIGNAL(timeout()),this,SLOT(UpdateTimerTick()));
        disconnect(svlifetime, SIGNAL(timeout()),this,SLOT(ServerTimeout()));
        disconnect(IOAlarmtimer, SIGNAL(timeout()),this,SLOT(IOAlarmTick()));

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
    HistoryEvents();
}

void MainWindow::IOAlarmTick()
{
    ReadDI(client);
    ReadDO(client);
    DisplayDI();
//    DisplayDO();

}

void MainWindow::JogRBTimer()
{

}

void MainWindow::Clock()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
//    QDateTime date = QDateTime::currentDateTime();
//    QString time_text = date.toString("dd.MM.yyyy hh:mm:ss");
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
           disconnect(IOAlarmtimer, SIGNAL(timeout()),this,SLOT(IOAlarmTick()));
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
           connect(IOAlarmtimer, SIGNAL(timeout()),this,SLOT(IOAlarmTick()));
           IOAlarmtimer->start(50);




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



void MainWindow::JogProcess(int number)
{
//    if(number == 0)
//    {
//        nodeid = ChooseRobot(robotnum);
//        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
//        qDebug() << count++;
//    }


}

void MainWindow::SetSttbar(bool bset)
{
    if (!bset)
    {
        ui->cbEnableDO->setEnabled(false);
        ui->btnDataAdd->setEnabled(false);
        ui->btnSendProg->setEnabled(false);
        ui->btnWriteProg->setEnabled(false);
        ui->btnCompProg->setEnabled(false);
        ui->btnOpenPts->setEnabled(false);
        ui->btnSendPoints->setEnabled(false);
        ui->tab_Points->setEnabled(false);
        ui->cbEnableDO->setEnabled(false);
        ui->btnOkpass->setEnabled(false);
        ui->tab_Jog->setEnabled(false);
    }
    else
    {
        ui->cbEnableDO->setEnabled(true);
        ui->btnDataAdd->setEnabled(true);
        ui->btnSendProg->setEnabled(true);
        ui->btnWriteProg->setEnabled(true);
        ui->btnCompProg->setEnabled(true);
        ui->btnOpenPts->setEnabled(true);
        ui->btnSendPoints->setEnabled(true);
        ui->tab_Points->setEnabled(true);
        ui->cbEnableDO->setEnabled(true);
        ui->btnOkpass->setEnabled(true);
        ui->tab_Jog->setEnabled(true);
    }
}

void MainWindow::CheckCMDAck()
{
    int ncheck = 0;
    int nosend = 0;
    QString chstrPacketData = checksend(StrPacketData);
    while (ncheck != 1 && nosend < 100)
    {
        QThread::msleep(1);
        ncheck = checkprogsend(chstrPacketData); // a function that check if command is sent
        nosend++;
    }

    if (nosend == 100)
    {
        QMessageBox::critical(this, "Caution", "Send CMD Failed!!!");
        return;
    }
    else
        qDebug() << "Send CMD successfully";
}

void MainWindow::HistoryEvents()
{




//    qDebug()  << bservosttpre << bservostt;
    if (bservostt != bservosttpre)
    {
        bservosttpre = bservostt;

        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {

            operevent  = new QTableWidgetItem;


            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                if (bservostt)
                    operevent->setText("Servo is turned on");
                else
                    operevent->setText("Servo is turned off");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;
    }
    if (brbmode != brbmodepre)
    {
        brbmodepre = brbmode;
        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {
            operevent  = new QTableWidgetItem;
            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                if (brbmode)
                    operevent->setText("Controller is changed to Repeat Mode");
                else
                    operevent->setText("Controller is changed to Teach Mode");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;
    }
    if (blockrbc != blockrbcpre)
    {
        blockrbcpre = blockrbc;
        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {
            operevent  = new QTableWidgetItem;
            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                if (blockrbc)
                    operevent->setText("The controller is unlocked");
                else
                    operevent->setText("The controller is locked");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;
    }
    if (nseclevel != nseclevelpre)
    {
        nseclevelpre = nseclevel;
        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {
            operevent  = new QTableWidgetItem;
            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                if (nseclevel == 0)
                    operevent->setText("The controller is OPERATION");
                else if (nseclevel == 1)
                    operevent->setText("The controller is EDIT");
                else if (nseclevel == 2)
                    operevent->setText("The controller is MANAGEMENT");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;
    }
//    qDebug() << strAlarm << strAlarmpre;
    if (strAlarm != "0")
    {
        if (strAlarmpre == "0")
        {
            for (int j=0; j<ui->tabAlarmHis->columnCount();j++)
            {
                alaevent  = new QTableWidgetItem;
                if (j==0)
                {
                    alaevent->setText(formattedtime);
                }
                if (j==1)
                {
                    alaevent->setText(strAlarm);
                }
                ui->tabAlarmHis->setItem(nalaeventcnt,j,alaevent);
            }
            nalaeventcnt++;
            strAlarmpre = strAlarm;
        }
    }
    else if (strAlarm == "0")
        strAlarmpre = strAlarm;



}





void MainWindow::ReadData(UA_Client *client) // SCARA Data
{

    // Number of clients
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Clientcntstt"), &value);
    numclient = *(UA_Int32*)value.data ;
    QString NoClient = QString::number(numclient);
    ui->lnENoclients->setText(NoClient);

    // SCARA Data

    // Servo Status
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/ServoStt"), &value);
    bservostt = *(UA_Boolean*)value.data ;
    QString servostt = Dispservostt(bservostt);
    ui->lnE_ServoStt1->setText(servostt);
    // System Status
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/SystemStt"), &value);
    nsystemstt = *(UA_Int32*)value.data ;
    QString sysstt = Dispsysstt(nsystemstt);
    ui->lnE_SysStt1->setText(sysstt);
    // Coordinate
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Coordinate"), &value);
    ncoord = *(UA_Int32*)value.data ;
    QString coordd = Dispcoord(ncoord);
    ui->lnE_Coord1->setText(coordd);
    // Mode
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Mode"), &value);
    brbmode = *(UA_Boolean*)value.data ;
    QString mode = Dispmode(brbmode);
    ui->lnE_Mode1->setText(mode);
    // Security Level
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/SecLevel"), &value);
    nseclevel = *(UA_Int32*)value.data ;
    QString seclvl = Dispseclvl(nseclevel);
    ui->lnE_Seclvl1->setText(seclvl);
    // Tool Number
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/ToolNumber"), &value);
    ntoolnum = *(UA_Int32*)value.data ;
    QString toolnum = QString::number(ntoolnum);
    ui->lnE_ToolNum1->setText(toolnum);
    // Jogging Speed
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/JogSpeed"), &value);
    njogsp = *(UA_Int32*)value.data ;
    QString jspeed = Dispjogsp(njogsp);
    ui->lnE_JogSp1->setText(jspeed);
    // Lock/Unlock controller
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/LockRBC"), &value);
    blockrbc = *(UA_Boolean*)value.data ;
    QString lockrbc = DispRBC(blockrbc);
    ui->lnELockRBC1->setText(lockrbc);

    //
//    UA_Byte bytee;
//    UA_Client_readEventNotifierAttribute(client, UA_NODEID("ns=4;s=Robot1/IOSend"), &bytee);

//    if(bytee == 1)
//    qDebug() << bytee;

    //x
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ1"), &value);
    dx = *(UA_Double*)value.data ;
    QString R1x = QString::number(dx);
    ui->lnERecv_x->setText(R1x);
    //y
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ2"), &value);
    dy = *(UA_Double*)value.data ;
    QString R1y = QString::number(dy);
    ui->lnERecv_y->setText(R1y);
    //z
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ3"), &value);
    dz = *(UA_Double*)value.data ;
    QString R1z = QString::number(dz);
    ui->lnERecv_z->setText(R1z);
    //roll
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ4"), &value);
    droll = *(UA_Double*)value.data ;
    QString R1roll = QString::number(droll);
    ui->lnERecv_roll->setText(R1roll);
    //pitch
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ5"), &value);
    dpitch = *(UA_Double*)value.data ;
    QString R1pitch = QString::number(dpitch);
    ui->lnERecv_pitch->setText(R1pitch);
    //yaw
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/XYZ6"), &value);
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
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta3"), &value);
    dd3 = *(UA_Double*)value.data ;
    QString R1d3 = QString::number(dd3);
    ui->lnERecv_d3->setText(R1d3);
    //theta4
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/theta4"), &value);
    dtheta4 = *(UA_Double*)value.data ;
    QString R1theta4 = QString::number(dtheta4);
    ui->lnERecv_theta4->setText(R1theta4);
    //CMDAck
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/CMDAck"), &value); //CMDAck
    sName = get_str_to_variant(&value);
    len = getlength(&value);
    QString strName = QString::fromStdString(sName);
    strName.resize(len);
    ui->lnECmd->setText(strName);
    //
//    bool bs = true;
//    UA_Variant_setScalarCopy(myVariant, &bs, &UA_TYPES[UA_TYPES_BOOLEAN]);
//    UA_Client_writeValueAttribute(client, UA_NODEID("ns=4;s=Robot1/Activated"), myVariant);

//    qDebug() << count;






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

void MainWindow::Alarm(UA_Client *client)
{

    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/AlarmMsg"), &value);
    sAlarm = get_str_to_variant(&value);
    bAlarm = getlength(&value);
    strAlarm = QString::fromStdString(sAlarm);
    strAlarm.resize(bAlarm);
    if (strAlarm != "0")
    {
//        strAlarmpre = strAlarm;

    }
    ui->lnERB1Ala->setText(strAlarm);


}

void MainWindow::ReadDI(UA_Client *client)
{
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    // group 1
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/DIgroup1"), &value);
    DIgroup1  =  *(UA_Byte*)value.data ;
    if ((DIgroup1 & 1) == 1)
        ui->lbDIStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    if ((DIgroup1 & 2) == 2)
        ui->lbDIStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    if ((DIgroup1 & 4) == 4)
        ui->lbDIStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup1 & 8) == 8)
        ui->lbDIStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup1 & 16) == 16)
        ui->lbDIStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup1 & 32) == 32)
        ui->lbDIStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup1 & 64) == 64)
        ui->lbDIStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup1 & 128) == 128)
        ui->lbDIStt8->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt8->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    // group 2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/DIgroup2"), &value);
    DIgroup2  =  *(UA_Byte*)value.data ;
    if ((DIgroup2 & 1) == 1)
        ui->lbDIStt9->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 2) == 2)
        ui->lbDIStt10->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt10->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 4) == 4)
        ui->lbDIStt11->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt11->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 8) == 8)
        ui->lbDIStt12->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt12->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 16) == 16)
        ui->lbDIStt13->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt13->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 32) == 32)
        ui->lbDIStt14->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt14->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 64) == 64)
        ui->lbDIStt15->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt15->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DIgroup2 & 128) == 128)
        ui->lbDIStt16->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDIStt16->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));




}

void MainWindow::ReadDO(UA_Client *client)
{
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    // group 1
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/DOgroup1"), &value);
    DOgroup1  =  *(UA_Byte*)value.data ;
    if ((DOgroup1 & 1) == 1)
        ui->lbDOStt1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 2) == 2)
        ui->lbDOStt2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 4) == 4)
        ui->lbDOStt3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 8) == 8)
        ui->lbDOStt4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 16) == 16)
        ui->lbDOStt5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 32) == 32)
        ui->lbDOStt6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 64) == 64)
        ui->lbDOStt7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup1 & 128) == 128)
        ui->lbDOStt8->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt8->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    // group 2
    UA_Client_readValueAttribute(client, UA_NODEID("ns=4;s=Robot1/DOgroup2"), &value);
    DOgroup2  =  *(UA_Byte*)value.data ;
    if ((DOgroup2 & 1) == 1)
        ui->lbDOStt9->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt9->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 2) == 2)
        ui->lbDOStt10->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt10->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 4) == 4)
        ui->lbDOStt11->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt11->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 8) == 8)
        ui->lbDOStt12->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt12->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 16) == 16)
        ui->lbDOStt13->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt13->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 32) == 32)
        ui->lbDOStt14->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt14->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 64) == 64)
        ui->lbDOStt15->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt15->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    if ((DOgroup2 & 128) == 128)
        ui->lbDOStt16->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
    else
        ui->lbDOStt16->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

}

void MainWindow::DisplayDI()
{
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (nDIgroup == 1)
    {
        QString DIdecval1 = QString::number(DIgroup1);
        ui->lnEDIdecval->setText(DIdecval1);
        QString hexval1 = QString("%1").arg(DIgroup1, 4, 16, QLatin1Char( '0' ));
        ui->lnEhexval->setText(hexval1);
        if ((DIgroup1 & 1) == 1)
            ui->lbDI0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 2) == 2)
            ui->lbDI1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 4) == 4)
            ui->lbDI2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 8) == 8)
            ui->lbDI3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 16) == 16)
            ui->lbDI4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 32) == 32)
            ui->lbDI5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 64) == 64)
            ui->lbDI6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup1 & 128) == 128)
            ui->lbDI7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }
    if (nDIgroup == 2)
    {
        QString DIdecval2 = QString::number(DIgroup2);
        ui->lnEDIdecval->setText(DIdecval2);
        QString hexval2 = QString("%1").arg(DIgroup2, 4, 16, QLatin1Char( '0' ));
        ui->lnEhexval->setText(hexval2);
        if ((DIgroup2 & 1) == 1)
            ui->lbDI0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 2) == 2)
            ui->lbDI1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 4) == 4)
            ui->lbDI2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 8) == 8)
            ui->lbDI3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 16) == 16)
            ui->lbDI4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 32) == 32)
            ui->lbDI5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 64) == 64)
            ui->lbDI6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        if ((DIgroup2 & 128) == 128)
            ui->lbDI7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
        else
            ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }

}

void MainWindow::DisplayDO()
{
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (nDOgroup == 1)
    {
        QString DOdecval1 = QString::number(DOgroup1);
        ui->lnEDODec->setText(DOdecval1);
        QString DOhexval1 = QString("%1").arg(DOgroup1, 4, 16, QLatin1Char( '0' ));
        ui->lnEDOHex->setText(DOhexval1);
        if ((DOgroup1 & 1) == 1)
        {
            ui->lbDO0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO1->setCheckable(true);
                ui->btnDO1->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO1->setCheckable(false);
                ui->btnDO1->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }

        }
        if ((DOgroup1 & 2) == 2)
        {
            ui->lbDO1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO2->setCheckable(true);
                ui->btnDO2->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO2->setCheckable(false);
                ui->btnDO2->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 4) == 4)
        {
            ui->lbDO2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO3->setCheckable(true);
                ui->btnDO3->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO3->setCheckable(false);
                ui->btnDO3->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 8) == 8)
        {
            ui->lbDO3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO4->setCheckable(true);
                ui->btnDO4->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO4->setCheckable(false);
                ui->btnDO4->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 16) == 16)
        {
            ui->lbDO4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO5->setCheckable(true);
                ui->btnDO5->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO5->setCheckable(false);
                ui->btnDO5->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 32) == 32)
        {
            ui->lbDO5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO6->setCheckable(true);
                ui->btnDO6->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO6->setCheckable(false);
                ui->btnDO6->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 64) == 64)
        {
            ui->lbDO6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO7->setCheckable(true);
                ui->btnDO7->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO7->setCheckable(false);
                ui->btnDO7->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup1 & 128) == 128)
        {
            ui->lbDO7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO8->setCheckable(true);
                ui->btnDO8->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO8->setCheckable(false);
                ui->btnDO8->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
    }

    if (nDOgroup == 2)
    {
        QString DOdecval2 = QString::number(DOgroup2);
        ui->lnEDODec->setText(DOdecval2);
        QString DOhexval2 = QString("%1").arg(DOgroup2, 4, 16, QLatin1Char( '0' ));
        ui->lnEDOHex->setText(DOhexval2);
        if ((DOgroup2 & 1) == 1)
        {
            ui->lbDO0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO1->setCheckable(true);
                ui->btnDO1->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO1->setCheckable(false);
                ui->btnDO1->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }

        }
        if ((DOgroup2 & 2) == 2)
        {
            ui->lbDO1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO2->setCheckable(true);
                ui->btnDO2->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO2->setCheckable(false);
                ui->btnDO2->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 4) == 4)
        {
            ui->lbDO2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO3->setCheckable(true);
                ui->btnDO3->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO3->setCheckable(false);
                ui->btnDO3->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 8) == 8)
        {
            ui->lbDO3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO4->setCheckable(true);
                ui->btnDO4->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO4->setCheckable(false);
                ui->btnDO4->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 16) == 16)
        {
            ui->lbDO4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO5->setCheckable(true);
                ui->btnDO5->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO5->setCheckable(false);
                ui->btnDO5->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 32) == 32)
        {
            ui->lbDO5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO6->setCheckable(true);
                ui->btnDO6->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO6->setCheckable(false);
                ui->btnDO6->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 64) == 64)
        {
            ui->lbDO6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO7->setCheckable(true);
                ui->btnDO7->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO7->setCheckable(false);
                ui->btnDO7->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
        if ((DOgroup2 & 128) == 128)
        {
            ui->lbDO7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO8->setCheckable(true);
                ui->btnDO8->setIcon(QIcon("./IOpics/onbtn.jpg"));
            }
        }
        else
        {
            ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
            if (bToggleDO)
            {
                ui->btnDO8->setCheckable(false);
                ui->btnDO8->setIcon(QIcon("./IOpics/offbtn.jpg"));
            }
        }
    }

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

void MainWindow::on_btnRBServo_toggled(bool checked)
{
    if (checked)
    {

        ui->btnRBServo->setIcon(QIcon("./IOpics/servo on.jpg"));
        servostt = "1";
        StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();

    }
    else
    {
        ui->btnRBServo->setIcon(QIcon("./IOpics/servo off.jpg"));
        servostt = "0";
        StrPacketData = QString("%1SVON,%2%3").arg(STX,servostt,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
}




void MainWindow::on_chbCoords_currentTextChanged(const QString &arg1)
{

    if (arg1 == "Joint Coordinates")
        coords = "0";
    else if (arg1 == "Cartesian Coordinates")
        coords = "1";
    else if (arg1 == "Tool Coordinates")
        coords = "2";
    else if (arg1 == "User Coordinates")
        coords = "3";
    else
        QMessageBox::critical(this, "Notice", "Please Choose Coordinate");

}


void MainWindow::on_btnJ1_neg_pressed()
{
    no_joint = "0";
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
        CheckCMDAck();


    }


}


void MainWindow::on_btnJ1_neg_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "0";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }



}


void MainWindow::on_btnJ1_pos_pressed()
{
    no_joint = "0";
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
        CheckCMDAck();
    }


}


void MainWindow::on_btnJ1_pos_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "0";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }


}


void MainWindow::on_btnJ2_neg_pressed()
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

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ2_neg_released()
{

    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "1";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ2_pos_pressed()
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

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ2_pos_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "1";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ3_neg_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ3_neg_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "2";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ3_pos_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ3_pos_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "2";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ4_neg_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ4_neg_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "3";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ4_pos_pressed()
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
        CheckCMDAck();

    }
}


void MainWindow::on_btnJ4_pos_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "3";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}

void MainWindow::on_btnJ5_neg_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ5_neg_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "4";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ5_pos_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ5_pos_released()
{    
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "4";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}


void MainWindow::on_btnJ6_neg_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ6_neg_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "5";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }


}


void MainWindow::on_btnJ6_pos_pressed()
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
        CheckCMDAck();
    }
}


void MainWindow::on_btnJ6_pos_released()
{
    coords = ChooseCoords(coords);
    if (coords == NULL)
    QMessageBox::critical(this, "Notice", "Please Choose Coordinate");
    else
    {
        no_joint = "5";
        StrPacketData = QString("%1STOP,%2%3").arg(STX,no_joint,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);

        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }

}





void MainWindow::on_btnSpeed_low_clicked()
{
    speed = "0";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();


}


void MainWindow::on_btnSpeed_med_clicked()
{
    speed = "1";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();


}


void MainWindow::on_btnSpeed_high_clicked()
{
    speed = "2";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();
}


void MainWindow::on_btnSpeed_top_clicked()
{
    speed = "3";
    StrPacketData = QString("%1SPED,%2%3").arg(STX,speed,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);

    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();

}

// PROGRAM TAB

// CMD program
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
//          QThread::msleep(50); // wait for sending command
          QString chstrPacketData = checksend(StrPacketData);
          int ncheck = 0;
          while (ncheck != 1 && nosend < 100)
          {
              QThread::msleep(1);
              ncheck = checkprogsend(chstrPacketData); // a function that check if command is sent
              nosend++;
          }

          if (nosend == 100)
          {
              QMessageBox::critical(this, "Caution", "Send Program Failed!!!");
              for (int j=0; j<ui->tabOperHis->columnCount();j++)
              {
                  operevent  = new QTableWidgetItem;
                  if (j==0)
                  {
                      operevent->setText(formattedtime);
                  }
                  if (j==1)
                  {
                      operevent->setText("Program is sent failed."
                                         " Please send it again.");
                  }
                  ui->tabOperHis->setItem(nopereventcnt,j,operevent);
              }
              nopereventcnt++;
              return;
          }
          else
          {           
              curline++;
          }
       }

       inputFile.close();


       StrPacketData = QString("%1SEPG,DONE %2%3").arg(STX,strCurJobName,ETX); //  finish sending program
       chPacketData = PackData(StrPacketData);
       set_str_to_variant(myVariant,chPacketData);
       UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
       QMessageBox::information(this, "Information", "Send Program OK!");
       for (int j=0; j<ui->tabOperHis->columnCount();j++)
       {
           operevent  = new QTableWidgetItem;
           if (j==0)
           {
               operevent->setText(formattedtime);
           }
           if (j==1)
           {
               operevent->setText("Program is sent succesfully.");
           }
           ui->tabOperHis->setItem(nopereventcnt,j,operevent);
       }
       nopereventcnt++;

    }
    else
    {
        ui->lnECmd->setText("Error String");

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
    for (int j=0; j<ui->tabOperHis->columnCount();j++)
    {
        operevent  = new QTableWidgetItem;
        if (j==0)
        {
            operevent->setText(formattedtime);
        }
        if (j==1)
        {
            operevent->setText("Program is compiling...");
        }
        ui->tabOperHis->setItem(nopereventcnt,j,operevent);
    }
    nopereventcnt++;
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
        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {
            operevent  = new QTableWidgetItem;
            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                operevent->setText("Program is compiled NG."
                                   " Please check program syntax.");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;

        return;
    }
    else
    {
        QMessageBox::information(this, "Information", "Compile OK");
        for (int j=0; j<ui->tabOperHis->columnCount();j++)
        {
            operevent  = new QTableWidgetItem;
            if (j==0)
            {
                operevent->setText(formattedtime);
            }
            if (j==1)
            {
                operevent->setText("Program is compiled OK.");
            }
            ui->tabOperHis->setItem(nopereventcnt,j,operevent);
        }
        nopereventcnt++;
    }

}

void MainWindow::on_btnRunprg_clicked()
{
    strCurJobName = ui->lnEProgName->text();
    StrPacketData = QString("%1RPRG,%2%3").arg(STX,strCurJobName,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);
    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();
    for (int j=0; j<ui->tabOperHis->columnCount();j++)
    {
        operevent  = new QTableWidgetItem;
        if (j==0)
        {
            operevent->setText(formattedtime);
        }
        if (j==1)
        {
            operevent->setText("Program is started in AUTOMATIC mode");
        }
        ui->tabOperHis->setItem(nopereventcnt,j,operevent);
    }
    nopereventcnt++;


}


void MainWindow::on_btnPauseprg_clicked()
{
    strCurJobName = ui->lnEProgName->text();
    StrPacketData = QString("%1PPRG,%2%3").arg(STX,strCurJobName,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);
    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();

}


void MainWindow::on_btnStopprg_clicked()
{
    strCurJobName = ui->lnEProgName->text();
    StrPacketData = QString("%1SPRG,%2%3").arg(STX,strCurJobName,ETX);
    chPacketData = PackData(StrPacketData);
    set_str_to_variant(myVariant,chPacketData);
    nodeid = ChooseRobot(robotnum);
    UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
    CheckCMDAck();
    for (int j=0; j<ui->tabOperHis->columnCount();j++)
    {
        operevent  = new QTableWidgetItem;
        if (j==0)
        {
            operevent->setText(formattedtime);
        }
        if (j==1)
        {
            operevent->setText("Program is stopped");
        }
        ui->tabOperHis->setItem(nopereventcnt,j,operevent);
    }
    nopereventcnt++;
}


// Points
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
//          QThread::msleep(50); // wait for sending command
          QString chstrPacketData = checksend(StrPacketData);
          int ncheck = 0;

          while (ncheck != 1 && nosend < 100)
          {
              QThread::msleep(1);
              ncheck = checkprogsend(chstrPacketData); // a function that check if command is sent
              nosend++;
          }

          if (nosend == 100)
          {
              QMessageBox::critical(this, "Caution", "Send Taught Points Failed!!!");
              for (int j=0; j<ui->tabOperHis->columnCount();j++)
              {
                  operevent  = new QTableWidgetItem;
                  if (j==0)
                  {
                      operevent->setText(formattedtime);
                  }
                  if (j==1)
                  {
                      operevent->setText("Teaching points data is sent failed."
                                         " Please send it again.");
                  }
                  ui->tabOperHis->setItem(nopereventcnt,j,operevent);
              }
              nopereventcnt++;
              return;
          }
          else
              curline++;
       }
       inputFile.close();

       StrPacketData = QString("%1SEPT,DONE %2%3").arg(STX,strPtsfilename,ETX); //  finish sending points
       chPacketData = PackData(StrPacketData);
       set_str_to_variant(myVariant,chPacketData);
       UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
       QMessageBox::information(this, "Information", "Send Taught Points OK!");
       for (int j=0; j<ui->tabOperHis->columnCount();j++)
       {
           operevent  = new QTableWidgetItem;
           if (j==0)
           {
               operevent->setText(formattedtime);
           }
           if (j==1)
           {
               operevent->setText("Teaching points data is sent OK.");
           }
           ui->tabOperHis->setItem(nopereventcnt,j,operevent);
       }
    }
    else
    {
//        ui->lnECmd->setText("Error String");
        QMessageBox::critical(this, "Caution", "The file is not exist");

    }

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

//        IOAlarmTick();



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
        ui->lnEDIdecval->clear();
        ui->lnEhexval->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    }

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
        ui->lnEDIdecval->clear();
        ui->lnEhexval->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
    }

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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }


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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    }


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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }


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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }

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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }

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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));



    }


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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }


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
        ui->lbDI7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDI0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }


}




// DO TAB




void MainWindow::on_cbEnableDO_stateChanged(int arg1)
{
    if (arg1)
    {
        bToggleDO = 1;

    }
    else
    {
        bToggleDO = 0;
        ui->btnDO1->setChecked(false);
        ui->btnDO2->setChecked(false);
        ui->btnDO3->setChecked(false);
        ui->btnDO4->setChecked(false);
        ui->btnDO5->setChecked(false);
        ui->btnDO6->setChecked(false);
        ui->btnDO7->setChecked(false);
        ui->btnDO8->setChecked(false);
        ui->btnDO1->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO2->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO3->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO4->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO5->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO6->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO7->setIcon(QIcon("./IOpics/offbtn.jpg"));
        ui->btnDO8->setIcon(QIcon("./IOpics/offbtn.jpg"));
    }
}


void MainWindow::on_chbDOgr1_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->chbDOgr2->setChecked(false);
        ui->chbDOgr3->setChecked(false);
        ui->chbDOgr4->setChecked(false);
        ui->chbDOgr5->setChecked(false);
        ui->chbDOgr6->setChecked(false);
        ui->chbDOgr7->setChecked(false);
        ui->chbDOgr8->setChecked(false);
        ui->chbDOgr9->setChecked(false);
        ui->chbDOgr10->setChecked(false);



        nDOgroup = 1;

        ui->lnEDOgr->setText("01");
        ui->lnEDO->setText("1-8");
        ui->lnEDO1->setText("01");
        ui->lnEDO2->setText("02");
        ui->lnEDO3->setText("03");
        ui->lnEDO4->setText("04");
        ui->lnEDO5->setText("05");
        ui->lnEDO6->setText("06");
        ui->lnEDO7->setText("07");
        ui->lnEDO8->setText("08");
    }
    else
    {
        nDOgroup = 0;

        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));



    }


}


void MainWindow::on_chbDOgr2_stateChanged(int arg1)
{
    if (arg1)
       {

           ui->chbDOgr1->setChecked(false);
           ui->chbDOgr3->setChecked(false);
           ui->chbDOgr4->setChecked(false);
           ui->chbDOgr5->setChecked(false);
           ui->chbDOgr6->setChecked(false);
           ui->chbDOgr7->setChecked(false);
           ui->chbDOgr8->setChecked(false);
           ui->chbDOgr9->setChecked(false);
           ui->chbDOgr10->setChecked(false);



           nDOgroup = 2;

           ui->lnEDOgr->setText("02");
           ui->lnEDO->setText("9-16");
           ui->lnEDO1->setText("9");
           ui->lnEDO2->setText("10");
           ui->lnEDO3->setText("11");
           ui->lnEDO4->setText("12");
           ui->lnEDO5->setText("13");
           ui->lnEDO6->setText("14");
           ui->lnEDO7->setText("15");
           ui->lnEDO8->setText("16");
        }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }

}


void MainWindow::on_chbDOgr3_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->chbDOgr1->setChecked(false);
        ui->chbDOgr2->setChecked(false);
        ui->chbDOgr4->setChecked(false);
        ui->chbDOgr5->setChecked(false);
        ui->chbDOgr6->setChecked(false);
        ui->chbDOgr7->setChecked(false);
        ui->chbDOgr8->setChecked(false);
        ui->chbDOgr9->setChecked(false);
        ui->chbDOgr10->setChecked(false);


        nDOgroup = 3;

        ui->lnEDIgr->setText("03");
        ui->lnEDO->setText("17-24");
        ui->lnEDO1->setText("17");
        ui->lnEDO2->setText("18");
        ui->lnEDO3->setText("19");
        ui->lnEDO4->setText("20");
        ui->lnEDO5->setText("21");
        ui->lnEDO6->setText("22");
        ui->lnEDO7->setText("23");
        ui->lnEDO8->setText("24");
    }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }



}


void MainWindow::on_chbDOgr4_stateChanged(int arg1)
{
    if (arg1)
        {

            ui->chbDOgr1->setChecked(false);
            ui->chbDOgr2->setChecked(false);
            ui->chbDOgr3->setChecked(false);
            ui->chbDOgr5->setChecked(false);
            ui->chbDOgr6->setChecked(false);
            ui->chbDOgr7->setChecked(false);
            ui->chbDOgr8->setChecked(false);
            ui->chbDOgr9->setChecked(false);
            ui->chbDOgr10->setChecked(false);


            nDOgroup = 4;

            ui->lnEDOgr->setText("04");
            ui->lnEDO->setText("25-32");
            ui->lnEDO1->setText("25");
            ui->lnEDO2->setText("26");
            ui->lnEDO3->setText("27");
            ui->lnEDO4->setText("28");
            ui->lnEDO5->setText("29");
            ui->lnEDO6->setText("30");
            ui->lnEDO7->setText("31");
            ui->lnEDO8->setText("32");
    }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

    }
}


void MainWindow::on_chbDOgr5_stateChanged(int arg1)
{
    if (arg1)
        {
            ui->chbDOgr1->setChecked(false);
            ui->chbDOgr2->setChecked(false);
            ui->chbDOgr3->setChecked(false);
            ui->chbDOgr4->setChecked(false);
            ui->chbDOgr6->setChecked(false);
            ui->chbDOgr7->setChecked(false);
            ui->chbDOgr8->setChecked(false);
            ui->chbDOgr9->setChecked(false);
            ui->chbDOgr10->setChecked(false);



            nDOgroup = 5;

            ui->lnEDOgr->setText("05");
            ui->lnEDO->setText("33-40");
            ui->lnEDO1->setText("33");
            ui->lnEDO2->setText("34");
            ui->lnEDO3->setText("35");
            ui->lnEDO4->setText("36");
            ui->lnEDO5->setText("37");
            ui->lnEDO6->setText("38");
            ui->lnEDO7->setText("39");
            ui->lnEDO8->setText("40");
        }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));



    }
}


void MainWindow::on_chbDOgr6_stateChanged(int arg1)
{
    if (arg1)
        {

            ui->chbDOgr1->setChecked(false);
            ui->chbDOgr2->setChecked(false);
            ui->chbDOgr3->setChecked(false);
            ui->chbDOgr4->setChecked(false);
            ui->chbDOgr5->setChecked(false);
            ui->chbDOgr7->setChecked(false);
            ui->chbDOgr8->setChecked(false);
            ui->chbDOgr9->setChecked(false);
            ui->chbDOgr10->setChecked(false);



            nDOgroup = 6;

            ui->lnEDOgr->setText("06");
            ui->lnEDO->setText("41-48");
            ui->lnEDO1->setText("41");
            ui->lnEDO2->setText("42");
            ui->lnEDO3->setText("43");
            ui->lnEDO4->setText("44");
            ui->lnEDO5->setText("45");
            ui->lnEDO6->setText("46");
            ui->lnEDO7->setText("47");
            ui->lnEDO8->setText("48");

        }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));




    }
}


void MainWindow::on_chbDOgr7_stateChanged(int arg1)
{
    if (arg1)
       {

           ui->chbDOgr1->setChecked(false);
           ui->chbDOgr2->setChecked(false);
           ui->chbDOgr3->setChecked(false);
           ui->chbDOgr4->setChecked(false);
           ui->chbDOgr5->setChecked(false);
           ui->chbDOgr6->setChecked(false);
           ui->chbDOgr8->setChecked(false);
           ui->chbDOgr9->setChecked(false);
           ui->chbDOgr10->setChecked(false);



           nDOgroup = 7;

           ui->lnEDOgr->setText("07");
           ui->lnEDO->setText("49-56");
           ui->lnEDO1->setText("49");
           ui->lnEDO2->setText("50");
           ui->lnEDO3->setText("51");
           ui->lnEDO4->setText("52");
           ui->lnEDO5->setText("53");
           ui->lnEDO6->setText("54");
           ui->lnEDO7->setText("55");
           ui->lnEDO8->setText("56");
    }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }
}


void MainWindow::on_chbDOgr8_stateChanged(int arg1)
{
    if (arg1)
        {

            ui->chbDOgr1->setChecked(false);
            ui->chbDOgr2->setChecked(false);
            ui->chbDOgr3->setChecked(false);
            ui->chbDOgr4->setChecked(false);
            ui->chbDOgr5->setChecked(false);
            ui->chbDOgr6->setChecked(false);
            ui->chbDOgr7->setChecked(false);
            ui->chbDOgr9->setChecked(false);
            ui->chbDOgr10->setChecked(false);



            nDOgroup = 8;

            ui->lnEDOgr->setText("08");
            ui->lnEDO->setText("57-64");
            ui->lnEDO1->setText("57");
            ui->lnEDO2->setText("58");
            ui->lnEDO3->setText("59");
            ui->lnEDO4->setText("60");
            ui->lnEDO5->setText("61");
            ui->lnEDO6->setText("62");
            ui->lnEDO7->setText("63");
            ui->lnEDO8->setText("64");

        }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }
}


void MainWindow::on_chbDOgr9_stateChanged(int arg1)
{
    if (arg1)
        {

            ui->chbDOgr1->setChecked(false);
            ui->chbDOgr2->setChecked(false);
            ui->chbDOgr3->setChecked(false);
            ui->chbDOgr4->setChecked(false);
            ui->chbDOgr5->setChecked(false);
            ui->chbDOgr6->setChecked(false);
            ui->chbDOgr7->setChecked(false);
            ui->chbDOgr8->setChecked(false);
            ui->chbDOgr10->setChecked(false);



            nDOgroup = 9;

            ui->lnEDOgr->setText("09");
            ui->lnEDO->setText("65-72");
            ui->lnEDO1->setText("65");
            ui->lnEDO2->setText("66");
            ui->lnEDO3->setText("67");
            ui->lnEDO4->setText("68");
            ui->lnEDO5->setText("69");
            ui->lnEDO6->setText("70");
            ui->lnEDO7->setText("71");
            ui->lnEDO8->setText("72");

        }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }
}


void MainWindow::on_chbDOgr10_stateChanged(int arg1)
{
    if (arg1)
       {

           ui->chbDOgr1->setChecked(false);
           ui->chbDOgr2->setChecked(false);
           ui->chbDOgr3->setChecked(false);
           ui->chbDOgr4->setChecked(false);
           ui->chbDOgr5->setChecked(false);
           ui->chbDOgr6->setChecked(false);
           ui->chbDOgr7->setChecked(false);
           ui->chbDOgr8->setChecked(false);
           ui->chbDOgr9->setChecked(false);



           nDOgroup = 10;

           ui->lnEDOgr->setText("10");
           ui->lnEDO->setText("73-80");
           ui->lnEDO1->setText("73");
           ui->lnEDO2->setText("74");
           ui->lnEDO3->setText("75");
           ui->lnEDO4->setText("76");
           ui->lnEDO5->setText("77");
           ui->lnEDO6->setText("78");
           ui->lnEDO7->setText("79");
           ui->lnEDO8->setText("80");

       }
    else
    {
        nDOgroup = 0;
        ui->lnEDOgr->clear();
        ui->lnEDO->clear();
        ui->lnEDO1->clear();
        ui->lnEDO2->clear();
        ui->lnEDO3->clear();
        ui->lnEDO4->clear();
        ui->lnEDO5->clear();
        ui->lnEDO6->clear();
        ui->lnEDO7->clear();
        ui->lnEDO8->clear();

        QPixmap offpix("./IOpics/Pilot light 2 (off).png");
        ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));
        ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


    }

}




void MainWindow::on_btnDO1_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 0;
    else if (nDOgroup == 2)
        nDObit = 8;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        qDebug() << 'b';
        if (checked)
        {
            ui->btnDO1->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO0->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));
            qDebug() << 'a';

        }
        else
        {
            ui->btnDO1->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO0->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO1->setChecked(false);


}


void MainWindow::on_btnDO2_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 1;
    else if (nDOgroup == 2)
        nDObit = 9;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO2->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO1->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO2->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO1->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO2->setChecked(false);

}


void MainWindow::on_btnDO3_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 2;
    else if (nDOgroup == 2)
        nDObit = 10;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO3->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO2->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO3->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO2->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO3->setChecked(false);

}


void MainWindow::on_btnDO4_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 3;
    else if (nDOgroup == 2)
        nDObit = 11;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO4->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO3->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO4->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO3->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO4->setChecked(false);


}


void MainWindow::on_btnDO5_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 4;
    else if (nDOgroup == 2)
        nDObit = 12;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO5->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO4->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO5->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO4->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO5->setChecked(false);


}


void MainWindow::on_btnDO6_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 5;
    else if (nDOgroup == 2)
        nDObit = 13;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO6->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO5->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO6->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO5->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO6->setChecked(false);

}


void MainWindow::on_btnDO7_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 6;
    else if (nDOgroup == 2)
        nDObit = 14;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO7->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO6->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO7->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO6->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO7->setChecked(false);

}


void MainWindow::on_btnDO8_toggled(bool checked)
{
    if (nDOgroup == 1)
        nDObit = 7;
    else if (nDOgroup == 2)
        nDObit = 15;
    QPixmap offpix("./IOpics/Pilot light 2 (off).png");
    QPixmap onpix("./IOpics/Green pilot light 2.png");
    if (bToggleDO == 1)
    {
        if (checked)
        {
            ui->btnDO8->setIcon(QIcon("./IOpics/onbtn.jpg"));
            ui->lbDO7->setPixmap(onpix.scaled(31,31,Qt::KeepAspectRatio));

        }
        else
        {
            ui->btnDO8->setIcon(QIcon("./IOpics/offbtn.jpg"));
            ui->lbDO7->setPixmap(offpix.scaled(31,31,Qt::KeepAspectRatio));


        }
        SendDO(client,nDOgroup,nDObit,checked);
        CheckCMDAck();
    }
    else
        ui->btnDO7->setChecked(false);

}



// Modify status bar

void MainWindow::on_combSeclvl_currentTextChanged(const QString &arg1)
{
    ui->btnRBMode->setEnabled(true);
    if (arg1 == "Edit")
    {
        ui->lnESecPass->clear();
        ui->btnOkpass->setEnabled(true);

    }
    else if (arg1 == "Management")
    {
        ui->lnESecPass->clear();
        ui->btnOkpass->setEnabled(true);
    }
    else if (arg1 == "Operation")
    {
        ui->btnOkpass->setEnabled(false);
        ui->lnESecPass->clear();
        SetSttbar(0);
        seclevel = "1";
        StrPacketData = QString("%1SECL,%2%3").arg(STX,seclevel,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();

    }

}


void MainWindow::on_btnOkpass_clicked()
{
    QString qstrpass;
    qstrpass = ui->lnESecPass->text();
    if (qstrpass == "1234")
    {
//        SetSttbar(1);
//        ui->tab_Program->setEnabled(true);
//        ui->tab_Points->setEnabled(true);
        seclevel = "2";
        StrPacketData = QString("%1SECL,%2%3").arg(STX,seclevel,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();

    }
    else if (qstrpass == "5678")
    {

        seclevel = "3";
        StrPacketData = QString("%1SECL,%2%3").arg(STX,seclevel,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
}

void MainWindow::on_btnSimRB_clicked()
{
    QProcess *process = new QProcess(this);
    QString file = "D:/Study/NCKH/5_SIMULATION/SD-SA600K-main-Teaching/build/debug/Display3DModel.exe" ;
    process->start(file);
}



void MainWindow::on_btnRBMode_toggled(bool checked)
{
    if (checked)
    {
        if (seclevel == "2" || seclevel == "3")
            SetSttbar(1);
        else if (seclevel == "1")
            ui->tab_Jog->setEnabled(true);
        ui->btnRBMode->setIcon(QIcon("./IOpics/teach mode.jpg"));
        rbMode = "1";
        StrPacketData = QString("%1MODE,%2%3").arg(STX,rbMode,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
    else
    {
        ui->tab_Jog->setEnabled(false);
        SetSttbar(0);
        ui->btnRBMode->setIcon(QIcon("./IOpics/auto mode.jpg"));
        rbMode = "0";
        StrPacketData = QString("%1MODE,%2%3").arg(STX,rbMode,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
}


void MainWindow::on_btnRBCLock_toggled(bool checked)
{
    if (checked)
    {
        ui->btnRBCLock->setIcon(QIcon("./IOpics/unlock RBC.jpg"));
        ui->btnRBMode->setEnabled(true);
        lockRBC = "1";
        StrPacketData = QString("%1LOCK,%2%3").arg(STX,lockRBC,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }
    else
    {
        ui->btnRBCLock->setIcon(QIcon("./IOpics/lock RBC.jpg"));
        ui->btnRBMode->setEnabled(false);
        SetSttbar(0);
        lockRBC = "0";
        StrPacketData = QString("%1LOCK,%2%3").arg(STX,lockRBC,ETX);
        chPacketData = PackData(StrPacketData);
        set_str_to_variant(myVariant,chPacketData);
        nodeid = ChooseRobot(robotnum);
        UA_Client_writeValueAttribute(client, UA_NODEID(nodeid), myVariant);
        CheckCMDAck();
    }


}







