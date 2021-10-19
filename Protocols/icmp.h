#ifndef ICMP_H
#define ICMP_H

#include <Protocols/basetransport.h>
#include <pcap/pcap.h>

#include <QObject>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Icmp : public BaseTransport {
  Q_OBJECT

  typedef unsigned char bit8;
  typedef unsigned short bit16;
  const int icmpSize = 8;

  struct IcmpHeader {
    bit8 icmp_type;      // 8 bits: Тип
    bit8 icmp_code;      // 8 bits: Код
    bit16 icmp_sum;      // 16 bits: Контрольная сумма
    uint32_t icmp_rest;  // 32 bits: Зависит от типа и кода
  };

  IcmpHeader icmpHeader;

 public:
  Icmp();

  virtual void deserializeHeader(const u_char *bytes, int offset);
  virtual bool isHeaderInvalid();
  virtual QString getFullData();
};

#endif  // ICMP_H
