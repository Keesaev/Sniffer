#ifndef SNIFFER_H
#define SNIFFER_H

#include <pcap/pcap.h>

#include <QObject>
#include <sstream>

#include "packet.hpp"

class Sniffer : public QObject {
  Q_OBJECT

  char* m_dev;
  pcap_t* m_handle;
  void captureSinglePacket();
  int m_packetCount, m_maxPacket;
  bool m_running = false;

 public:
  explicit Sniffer(QObject* parent = nullptr);
  ~Sniffer();

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
