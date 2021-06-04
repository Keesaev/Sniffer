#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <QTime>
#include <QMetaType>

class Packet
{
public:
    Packet(){

    }
    int number;
    QString sourceIp, destIp, protocol, length, fullData;
    QTime timestamp;
};

Q_DECLARE_METATYPE(Packet)
#endif // PACKETDATA_H
