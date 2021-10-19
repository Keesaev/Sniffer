#ifndef SNIFFER_H
#define SNIFFER_H

#include <Protocols/basetransport.h>
#include <Protocols/datalink.h>
#include <Protocols/network.h>
#include <Protocols/unknowntransport.h>
#include <factory.h>
#include <packet.h>
#include <pcap/pcap.h>

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <sstream>

using namespace std;

class Sniffer : public QObject {
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
  void closeHandle();
 signals:
  void packetDeserialized(const Packet packet);
};

#endif  // SNIFFER_H
