#include "udp.h"

Udp::Udp()
{

}

void Udp::deserializeHeader(const u_char *bytes, int offset) {
    string str(reinterpret_cast<const char*>(bytes), offset + udpHeaderSize);
    str = str.substr(offset, udpHeaderSize);
    stringstream stream(str);

    stream.read(reinterpret_cast<char*>(&udpHeader.udp_sport), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&udpHeader.udp_dport), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&udpHeader.udp_len), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&udpHeader.udp_chksum), sizeof(bit16));
}

bool Udp::isHeaderInvalid() {
    // TODO
    return false;
}

QString Udp::getFullData() {
    QString s =
        "\nProtocol:\tUDP\nSource port:\t" + QString::number(ntohs(udpHeader.udp_sport)) +
        "\nDestination port:\t" + QString::number(ntohs(udpHeader.udp_dport)) +
        "\nHeader length:\t" + QString::number(ntohs(udpHeader.udp_len)) +
        "\nChecksum:\t" + QString::number(ntohs(udpHeader.udp_chksum));
    return s;
}
