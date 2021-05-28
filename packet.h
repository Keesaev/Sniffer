#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <QTime>
#include <QMetaType>

class Packet
{
public:
    Packet(){

    }
    Packet(int n, QString sIp, QString dIp, QString p, QString l, QString f,QTime t) :
        number(n), sourceIp(sIp), destIp(dIp), protocol(p), length(l), fullData(f), timestamp(t){

    }
    int number;
    QString sourceIp, destIp, protocol, length, fullData;
    QTime timestamp;
};

Q_DECLARE_METATYPE(Packet)
#endif // PACKETDATA_H
