#include "protocol.h"
#include <stdio.h>



protocol::protocol(QObject *parent)
    : QObject{parent}
{


}
protocol* ptr = nullptr;
void protocol::MakeCrcSVON(QString &strPacketData)
{
    unsigned short usCheckSum = 0;
    unsigned short usPacketSize = strPacketData.length();
    QChar chETX;

    chETX = strPacketData.at(usPacketSize-1);
    strPacketData.chop(1);
    usPacketSize = usPacketSize - 1;

    int i;
    QString strCheckSum;
    QChar ch;

    for(i = 1; i < usPacketSize ; i++)
        {
            ch = strPacketData.at(i);
            char ch_ascii = ch.toLatin1();
            usCheckSum = usCheckSum ^ ch_ascii;
        }
     QString uschecksum = QString::number(usCheckSum);
     strCheckSum = QString(";%1%2").arg(uschecksum,chETX);
     strPacketData += strCheckSum;

}

//PacketData


//function to generate protocol from packetdata, calculate and insert CRC to protocol

protocol *getprotocolPtr()
{
    return ptr;
}
