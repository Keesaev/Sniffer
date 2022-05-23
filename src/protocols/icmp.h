#ifndef ICMP_H
#define ICMP_H

#include "base_transport.hpp"

class Icmp : public BaseTransport {
  typedef unsigned char bit8;
  typedef unsigned short bit16;
  const int icmpSize = 8;

  // HEADER

  bit8 icmp_type;      // 8 bits: Тип
  bit8 icmp_code;      // 8 bits: Код
  bit16 icmp_sum;      // 16 bits: Контрольная сумма
  uint32_t icmp_rest;  // 32 bits: Зависит от типа и кода

 public:
  void deserializeHeader(const u_char* bytes, int offset) final;
  virtual bool isHeaderInvalid() const final;
  virtual QString getFullData() const final;
};

#endif  // ICMP_H
