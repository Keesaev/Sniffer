#ifndef SNIFFER_H
#define SNIFFER_H

#include <pcap/pcap.h>

#include <QObject>

#include <memory>
#include <sstream>

#include "packet.hpp"

class Sniffer : public QObject {
  Q_OBJECT

  std::unique_ptr<pcap_t, void (*)(pcap_t*)> m_handle;

  int m_packetCount{0};
  bool m_running = false;
  char errbuf[PCAP_ERRBUF_SIZE];

  void captureSinglePacket();

 public:
  explicit Sniffer(QString const& device);
  ~Sniffer();

  bool isValid() const;
  void startCapture();
  void stopCapture();
 signals:
  void packetDeserialized(const Packet packet);
  void finished();
};

#endif  // SNIFFER_H
