#ifndef TCP_H
#define TCP_H

#include "base_transport.hpp"

#include <unordered_map>

class Tcp : public BaseTransport {
  typedef unsigned char bit8;
  typedef unsigned short bit16;
  typedef unsigned int bit32;
  const int tcpMaxHeaderSize = 60;
  const int tcpMinHeaderSize = 20;

  // TODO constexpr

  // https://en.wikipedia.org/wiki/Transmission_Control_Protocol
  const std::unordered_map<int, QString> flags = {
      {128, "CWR (Cognecion window reduced)\n"},
      {64, "ECE (ECN-Echo)\n"},
      {32, "URG (Urgent point)\n"},
      {16, "ACK (Acknowledgment)\n"},
      {8, "PSH (Push)\n"},
      {4, "RST (Reset)\n"},
      {2, "SYN (Synchronize)\n"},
      {1, "FIN (Final packet)\n"}};

  // HEADER

  bit16 tcp_sport;  // 16 bits:  Порт отправителя
  bit16 tcp_dport;  // 16 bits: Порт получателя
  bit32 tcp_seqn;  // 32 bits: Sequence number (порядковый номер)
  bit32 tcp_ack;  // 32 bits: Acknowledgment number (номер подтверждения)
  bit8 tcp_offx2;  // 8 bits: 4 бита Data offset (длина заголовка) и 4 бита
                   // зарезервировано
  // TODO
  bit8 tcp_flags;  // 8 bits: Флаги
  bit16 tcp_win;   // 16 bits: Размер окна
  bit16 tcp_sum;   // 16 bits: Контрольная сумма
  bit16 tcp_urp;  // 16 bits: Urgent point (указатель важности)

  int getOffset() const;
  QString getFlags() const;

 public:
  virtual void deserializeHeader(const u_char* bytes, int offset) final;
  virtual bool isHeaderInvalid() const final;
  virtual QString getFullData() const final;
};

#endif  // TCP_H
