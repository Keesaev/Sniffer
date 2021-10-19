#ifndef PACKET_HPP
#define PACKET_HPP

#include <QMetaType>
#include <QTime>

class Packet {
 public:
  Packet() {}
  int number;
  QString sourceIp, destIp, protocol, length, fullData;
  QTime timestamp;
};

Q_DECLARE_METATYPE(Packet)
#endif  // PACKET_HPP
