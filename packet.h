#ifndef PACKETDATA_H
#define PACKETDATA_H

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
#endif  // PACKETDATA_H
