#ifndef DATALINK_H
#define DATALINK_H

#include <string>
#include <unordered_map>

#include <QString>

class DataLink {
  // TODO move somewhere
  typedef unsigned char bit8;
  typedef unsigned short bit16;
  const int ethernetHeaderSize = 14;
  // TODO constexpr
  const std::unordered_map<int, QString> hexLetters = {
      {10, "a"}, {11, "b"}, {12, "c"}, {13, "d"}, {14, "e"}, {15, "f"},
  };

  // HEADER

  bit8 ether_dhost[6];  // 48 bits: Мак-адрес получателя
  bit8 ether_shost[6];  // 48 bits: Мак-адрес отправителя
  bit16 ether_type;  // 16 bits: Тип протокола уровня выше (8 = ip)

  // TODO move to separate class
  QString getMac(const bit8 addr[]) const;
  QString byteToHexString(unsigned char a) const;
  QString getSingleHexRegister(int b) const;

 public:
  void deserializeHeader(const u_char* bytes);
  QString getFullData() const;
  int getHeaderSize() const;
};

#endif  // DATALINK_H
