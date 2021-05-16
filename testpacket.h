#ifndef TESTPACKET_H
#define TESTPACKET_H

#include <QObject>
#include <string>
#include <QVariantMap>
#include <QVariant>
#include <qqml.h>

using namespace std;

class TestPacket : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    /*
    Q_PROPERTY(int timestamp READ getTimestamp)
    Q_PROPERTY(string sourceIp READ getSourceIp)
    Q_PROPERTY(string destIp READ getDestIp)
    Q_PROPERTY(string protocol READ getProtocol)
    Q_PROPERTY(string lenght READ getLength)
    Q_PROPERTY(QVariantMap dataLinkFullData READ getDataLinkFullData)
    Q_PROPERTY(QVariantMap networkFullData READ getNetworkFullData)
    Q_PROPERTY(QVariantMap transportFullData READ getTransportFullData)*/
public:
    explicit TestPacket(QObject *parent = nullptr);
    int number, timestamp;
    QString sourceIp, destIp, protocol, length;
    QVariantMap dataLinkFullData;
    QVariantMap networkFullData;
    QVariantMap transportFullData;

    Q_INVOKABLE int getNumber(){
        return number;
    }

    Q_INVOKABLE int getTimestamp(){
        return timestamp;
    }
    Q_INVOKABLE QString getSourceIp(){
        return sourceIp;
    }
    Q_INVOKABLE QString getDestIp(){
        return sourceIp;
    }
    Q_INVOKABLE QString getProtocol(){
        return protocol;
    }
    Q_INVOKABLE QString getLength(){
        return length;
    }
    Q_INVOKABLE QVariantMap getDataLinkFullData(){
        return dataLinkFullData;
    }
    Q_INVOKABLE QVariantMap getNetworkFullData(){
        return networkFullData;
    }
    Q_INVOKABLE QVariantMap getTransportFullData(){
        return transportFullData;
    }

signals:

};

#endif // TESTPACKET_H
