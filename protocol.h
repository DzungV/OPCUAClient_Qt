#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>



class protocol : public QObject
{
    Q_OBJECT
public:
    explicit protocol(QObject *parent = nullptr);

    void MakeCrcSVON(QString &strPacketData);

signals:

};

protocol *getprotocolPtr();

#endif // PROTOCOL_H
