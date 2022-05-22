#include "udp.h"

#include <pcap/pcap.h>

#include <sstream>
#include <string>

void Udp::deserializeHeader(const u_char* bytes, int offset) {
  std::string str(reinterpret_cast<const char*>(bytes), offset + udpHeaderSize);
  str = str.substr(offset, udpHeaderSize);
  std::stringstream stream(str);

  stream.read(reinterpret_cast<char*>(&udp_sport), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&udp_dport), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&udp_len), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&udp_chksum), sizeof(bit16));
}

bool Udp::isHeaderInvalid() const {
  // TODO
  return false;
}

QString Udp::getFullData() const {
  return "\nUDP\n\tSource port: " + QString::number(ntohs(udp_sport)) +
         "\n\tDestination port: " + QString::number(ntohs(udp_dport)) +
         "\n\tHeader length: " + QString::number(ntohs(udp_len)) +
         "\n\tChecksum: " + QString::number(ntohs(udp_chksum));
}
