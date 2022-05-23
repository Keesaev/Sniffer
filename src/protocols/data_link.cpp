#include "data_link.h"

#include <sstream>

void DataLink::deserializeHeader(const u_char* bytes) {
  std::string str(reinterpret_cast<const char*>(bytes), ethernetHeaderSize);
  std::stringstream stream(str);

  for (int i = 0; i < 6; i++) {
    stream >> ether_dhost[i];
  }

  for (int i = 0; i < 6; i++) {
    stream >> ether_shost[i];
  }
  // TODO
  // stringstream не умеет читать u_short, перегрузка >> не помогает, поэтому
  // так:

  // TODO ??
  stream >> reinterpret_cast<char*>(&ether_type),
      sizeof(bit16);  // ?
}

QString DataLink::getFullData() const {
  return "Ethernet II\n\tSource: " + getMac(ether_shost) +
         "\n\tDestination: " + getMac(ether_dhost) +
         "\n\tType: " + QString::number(ether_type);
}

QString DataLink::getMac(const bit8 addr[]) const {
  QString s = "";
  for (int i = 0; i < 6; i++) {
    s += byteToHexString(addr[i]) + ":";
  }
  s[s.length() - 1] = ' ';
  return s;
}

QString DataLink::byteToHexString(unsigned char a) const {
  int b = a / 16;
  int c = a % 16;

  return (getSingleHexRegister(b) + getSingleHexRegister(c));
}

QString DataLink::getSingleHexRegister(int b) const {
  if (b > 9) {
    const auto f = hexLetters.find(b);
    if (f != hexLetters.end()) {
      return f->second;
    } else {
      return "0";
    }
  } else {
    return QString((char)(48 + b));
  }
}

int DataLink::getHeaderSize() const {
  return ethernetHeaderSize;
}
