#ifndef SNIFFER_H
#define SNIFFER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <qqml.h>

#include <pcap/pcap.h>
#include <sstream>

#include <datalink.h>
#include <network.h>
#include <basetransport.h>
#include <unknowntransport.h>
#include <factory.h>
#include <packetdata.h>

using namespace std;

class Sniffer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    char *m_dev;
    pcap_t *m_handle;
    void captureSinglePacket();
    int packetCount;
public:
    explicit Sniffer(QObject *parent = nullptr);
    Q_INVOKABLE QVariantMap getDevs();
    Q_INVOKABLE void setDev(QString d);
    Q_INVOKABLE bool initPcap();
    Q_INVOKABLE void startLoopingCapture(int c);
    Q_INVOKABLE void stopCapture();
signals:
    void packetDeserialized(PacketData *packet);
};

#endif // SNIFFER_H
