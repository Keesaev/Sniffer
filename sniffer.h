#ifndef SNIFFER_H
#define SNIFFER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

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

    char *m_dev;
    pcap_t *m_handle;
    void captureSinglePacket();
    int m_packetCount, m_maxPacket;
    bool m_running = false;
public:
    explicit Sniffer(QObject *parent = nullptr);
    QVariantMap getDevs();
    void setDev(QString d);
    void setMaxPacket(int c);
    bool initPcap();
    void startLoopingCapture();
    void stopCapture();
signals:
    void packetDeserialized(const PacketData packet);
};

#endif // SNIFFER_H
