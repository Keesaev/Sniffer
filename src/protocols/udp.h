#ifndef UDP_H
#define UDP_H

#include "base_transport.hpp"

class Udp : public BaseTransport {
  typedef unsigned short bit16;
  const int udpHeaderSize = 8;

  bit16 udp_sport;   // 16 bits: Source port
  bit16 udp_dport;   // 16 bits: Destination port
  bit16 udp_len;     // 16 bits: Длина сообщения
  bit16 udp_chksum;  // 16 bits: Контрольная сумма

 public:
  virtual void deserializeHeader(const u_char* bytes, int offset) final;
  virtual bool isHeaderInvalid() const final;
  virtual QString getFullData() const final;
};

#endif  // UDP_H
