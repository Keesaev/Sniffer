#include "tcp.h"

#include <sstream>
#include <string>

#include <pcap/pcap.h>

void Tcp::deserializeHeader(const u_char* bytes, int offset) {
  std::string str(reinterpret_cast<const char*>(bytes),
                  offset + tcpMaxHeaderSize);
  str = str.substr(offset, tcpMaxHeaderSize);
  std::stringstream stream(str);

  stream.read(reinterpret_cast<char*>(&tcp_sport), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&tcp_dport), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&tcp_seqn), sizeof(bit32));
  stream.read(reinterpret_cast<char*>(&tcp_ack), sizeof(bit32));
  stream >> tcp_offx2 >> tcp_flags;
  stream.read(reinterpret_cast<char*>(&tcp_win), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&tcp_sum), sizeof(bit16));
  stream.read(reinterpret_cast<char*>(&tcp_urp), sizeof(bit16));
}

bool Tcp::isHeaderInvalid() const {
  unsigned int size_tcp = getOffset() * 4;
  if ((int)size_tcp < tcpMinHeaderSize || (int)size_tcp > tcpMaxHeaderSize)
    return true;
  else
    return false;
}

QString Tcp::getFullData() const {
  QString s = "\nTCP\n\tSource port: " + QString::number(htons(tcp_sport)) +
              "\n\tDestination port: " + QString::number(htons(tcp_dport)) +
              "\n\tSequence number: " + QString::number(htonl(tcp_seqn)) +
              "\n\tAcknowledgment Number: " + QString::number(htonl(tcp_ack)) +
              "\n\tData offset: " + QString::number(getOffset()) +
              "\n\tFlags: " + getFlags() +
              "Window size: " + QString::number(htons(tcp_win)) +
              "\n\tChecksum: " + QString::number(htons(tcp_sum)) +
              "\n\tUrgent Point: " + QString::number(htons(tcp_urp));
  return s;
}

int Tcp::getOffset() const {
  return ((tcp_offx2) >> 4);
}

// https://en.wikipedia.org/wiki/Transmission_Control_Protocol
// https://networkguru.ru/protokol-transportnogo-urovnia-tcp-chto-nuzhno-znat/
QString Tcp::getFlags() const {
  if (tcp_offx2 & 1)
    return "NC (Nonce Sum)\t";

  QString s = "";
  for (const auto& i : flags) {
    if (tcp_flags & i.first)
      s += i.second + "\t";
  }
  return s;
}
