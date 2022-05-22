#include "icmp.h"

#include <sstream>
#include <string>

#include <pcap/pcap.h>  // ntohs

void Icmp::deserializeHeader(const u_char* bytes, int offset) {
  std::string str(reinterpret_cast<const char*>(bytes), offset + icmpSize);
  str = str.substr(offset, icmpSize);
  std::stringstream stream(str);

  stream >> icmp_type;
  stream >> icmp_code;
  stream.read(reinterpret_cast<char*>(&icmp_sum), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&icmp_rest), sizeof(uint32_t));
}

bool Icmp::isHeaderInvalid() const {
  //  TODO
  return false;
}

QString Icmp::getFullData() const {
  return "\nICMP\n\tType: " + QString::number(static_cast<int>(icmp_type)) +
         "\n\tCode: " + QString::number(static_cast<int>(icmp_code)) +
         "\n\tChecksum: " + QString::number(ntohs(icmp_sum)) +
         "\n\tOptions: " + QString::number(ntohs(icmp_rest));
}
