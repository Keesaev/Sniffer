#ifndef PACKETDATA_H
#define PACKETDATA_H

#include <QObject>
#include <string>
#include <vector>
#include <pcap/pcap.h>
#include <qqml.h>

using namespace std;

class PacketData : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PacketData(QObject *parent = nullptr);

    int number;
    QString timestamp, sourceIp, destIp, protocol, length, fullData;
    Q_INVOKABLE int getNumber(){ return number; }
    Q_INVOKABLE QString getTimestamp(){ return timestamp; }
    Q_INVOKABLE QString getSourceIp(){ return sourceIp; }
    Q_INVOKABLE QString getDestIp(){ return sourceIp; }
    Q_INVOKABLE QString getProtocol(){ return protocol; }
    Q_INVOKABLE QString getLength(){ return length; }
    Q_INVOKABLE QString getFullData() {return fullData; }
};

#endif // PACKETDATA_H
