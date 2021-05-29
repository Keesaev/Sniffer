#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <pcap/pcap.h>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <map>

#include <iostream>

using namespace std;

class Network : public QObject
{
    Q_OBJECT

    typedef unsigned char bit8;
    typedef unsigned short bit16;
    const int ipMaxHeaderSize = 60;
    const int ipMinHeaderSize = 20;
    const int ethernetHeaderSize = 14;

    // https://ru.wikipedia.org/wiki/Explicit_Congestion_Notification
    // https://www.juniper.net/documentation/us/en/software/junos/cos/topics/concept/cos-qfx-series-explicit-congestion-notification-understanding.html
    map<int, QString> ecn = {
        {0, "Non-ECT - not ECN-capable"},
        {1, "ECT(1) — Endpoints of the transport protocol are ECN-capable"},
        {2, "ECT(0)—Endpoints of the transport protocol are ECN-capable"},
        {3, "CE—Congestion experienced"}
    };

    // https://ru.wikipedia.org/wiki/DiffServ_Code_Point
    map<int, QString> diffServ = {
        {0, "CS0"},
        {8, "CS1"},
        {16, "CS2"},
        {24, "CS3"},
        {32, "CS4"},
        {40, "CS5"},
        {48, "CS6"},
        {56, "CS7"},
    };

    // https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
    map<int, QString> transportProts = {
        {0, "HOPOPT"},
        {1, "ICMP"},
        {2, "IGMP"},
        {4, "IPv4"},
        {6, "TCP"},
        {8, "EGP"},
        {9, "IGP"},
        {17, "UDP"},
        {29, "ISO-TP4"},
        {30, "NETBLT"},
        {41, "IPv6"},
        {56, "TLSP"},
        {88, "EIGRP"},
        {89, "OSPF"},
        {127, "CRUDP"},
        {132, "FC"},
        {141, "WESP"},
        {142, "ROHC"}
    };

    // https://en.wikipedia.org/wiki/IPv4#Header
    struct IpHeader{
        bit8 ip_vhl;  // 8 bits:   Version (4 bits) + Header Length (4 bits)
        bit8 ip_tos;  // 8 bits:   Type of service (тип обслуживания)
        bit16 ip_len; // 16 bits:   Длина пакета
        bit16 ip_id;  // 16 bits:   Идентификатор пакета
        bit16 ip_off; // 16 bits:    Flags (3 bits) + смещение фрагмента (13 bits)
        bit8 ip_ttl;  // 8 bits:     Time to live (число хопов)
        bit8 ip_p;    // 8 bits:   Тип протокола (TCP, UDP, ICMP)
        bit16 ip_sum; // 16 bits:  Контрольная сумма
        struct in_addr ip_src, ip_dst; // 32 bits each
    };

    IpHeader ipHeader;

    QString getAddress(in_addr addr);
    QString getDiffServ();   // 6 бит ip_tos
    QString getECN();        // 2 бита ip_tos
    QString getFlags();      // 3 бита ip_off

    int getVersion();
    int getOffset();

public:
    explicit Network(QObject *parent = nullptr);

    QString getFullData();
    void deserializeHeader(const u_char* bytes);
    bool isHeaderEmpty();
    int getHeaderSize();
    int getProtocol();
    QString getProtocolName();
    QString getSourceIp();
    QString getDestIp();

signals:

};

#endif // NETWORK_H
