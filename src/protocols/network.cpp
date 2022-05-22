#include "network.h"

#include <sstream>
#include <string>

void Network::deserializeHeader(const u_char* bytes) {
  // Читаем последовательность длиной ethernetSize + ipMaxSize
  std::string str(reinterpret_cast<const char*>(bytes),
                  ethernetHeaderSize + ipMaxHeaderSize);
  str = str.substr(ethernetHeaderSize, ipMaxHeaderSize);
  std::stringstream stream(str);

  stream >> ip_vhl;
  stream >> ip_tos;
  stream.read(reinterpret_cast<char*>(&ip_len), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&ip_id), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&ip_off), sizeof(bit16));
  stream >> ip_ttl;
  stream >> ip_p;
  stream.read(reinterpret_cast<char*>(&ip_sum), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&ip_src), sizeof(in_addr));
  stream.read(reinterpret_cast<char*>(&ip_dst), sizeof(in_addr));
}

QString Network::getFullData() const {
  return "\nIPv4\n\tVersion: " + QString::number(getVersion()) +
         "\n\tInternet Header Length: " + QString::number(getHeaderSize()) +
         "\n\tDifferenciated services code point: " + getDiffServ() +
         "\n\tExplicit Congestion Notification: " + getECN() +
         "\n\tTotal length: " + QString::number(ntohs(ip_len)) +
         "\n\tIdentification: " + QString::number(ntohs(ip_id)) +
         "\n\tFlags: " + getFlags() +
         "\n\tFragment offset: " + QString::number(getOffset()) +
         "\n\tTime to live: " + QString::number(static_cast<int>(ip_ttl)) +
         "\n\tProtocol: " + QString::number(getProtocol()) + "(" +
         getProtocolName() + ")" +
         "\n\tHeader checksum: " + QString::number(ntohs(ip_sum)) +
         "\n\tSource: " + getAddress(ip_src) +
         "\n\tDestination: " + getAddress(ip_dst);
}

bool Network::isHeaderEmpty() const {  // TODO
  unsigned int size_ip = getHeaderSize() * 4;
  if (size_ip < ipMinHeaderSize)
    return true;
  else {
    return false;
  }
}

int Network::getProtocol() const {
  return ip_p;
}

QString Network::getProtocolName() const {
  int p = static_cast<int>(ip_p);
  QString s = "";

  const auto res = transportProts.find(p);
  if (res != transportProts.end())
    s = res->second;
  else if (p >= 144 && p <= 252)
    s = "Unassigned";
  else
    s = "Unknown";
  return s;
}

// Читаем левые 4 бита поля ip_vhl
int Network::getHeaderSize() const {
  return ((ip_vhl)&0x0f) * 4;
}

QString Network::getSourceIp() const {
  return getAddress(ip_src);
}

QString Network::getDestIp() const {
  return getAddress(ip_dst);
}

QString Network::getAddress(in_addr addr) const {
  char cAddr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(addr), cAddr, INET_ADDRSTRLEN);
  return cAddr;
}

QString Network::getECN() const {
  int e = ip_tos & 3;
  QString s = "Decimal value: " + QString::number(e);

  const auto res = ecn.find(e);
  if (res != ecn.end())
    s += " (" + res->second + ")";

  return s;
}

QString Network::getDiffServ() const {
  int ds = ip_tos >> 2;
  QString s = "Decimal value: " + QString::number(ds);

  const auto res = diffServ.find(ds);
  if (res != diffServ.end())
    s += " (DSCP: " + res->second + ")";

  return s;
}

// https://www.pearsonitcertification.com/articles/article.aspx?p=1843887
QString Network::getFlags() const {
  QString s = "";
  int a = ntohs(ip_off);
  bool df = (a >> 14) & 1;
  bool mf = (a >> 13) & 1;

  s += df ? "Don't fragment " : "";
  s += mf ? "More fragments" : "";

  if (s.isEmpty())
    s = "Not set";

  return s;
}

// Читаем правые 4 бита поля ip_vhl
int Network::getVersion() const {
  return ((ip_vhl) >> 4);
}

// Берем всё кроме левых 3 битов в ip_off
int Network::getOffset() const {
  return (ntohs(ip_off) & 8191);
}
