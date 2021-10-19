#include "udp.h"

Udp::Udp() {}

void Udp::deserializeHeader(const u_char *bytes, int offset) {
  string str(reinterpret_cast<const char *>(bytes), offset + udpHeaderSize);
  str = str.substr(offset, udpHeaderSize);
  stringstream stream(str);

  stream.read(reinterpret_cast<char *>(&udpHeader.udp_sport), sizeof(bit16));
  stream.read(reinterpret_cast<char *>(&udpHeader.udp_dport), sizeof(bit16));
  stream.read(reinterpret_cast<char *>(&udpHeader.udp_len), sizeof(bit16));
  stream.read(reinterpret_cast<char *>(&udpHeader.udp_chksum), sizeof(bit16));
}

bool Udp::isHeaderInvalid() {
  // TODO
  return false;
}

QString Udp::getFullData() {
  QString s =
      "\nUDP\n\tSource port: " + QString::number(ntohs(udpHeader.udp_sport)) +
      "\n\tDestination port: " + QString::number(ntohs(udpHeader.udp_dport)) +
      "\n\tHeader length: " + QString::number(ntohs(udpHeader.udp_len)) +
      "\n\tChecksum: " + QString::number(ntohs(udpHeader.udp_chksum));
  return s;
}
