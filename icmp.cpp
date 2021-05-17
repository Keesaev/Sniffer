#include "icmp.h"

Icmp::Icmp()
{

}

void Icmp::deserializeHeader(const u_char *bytes, int offset) {
    string str(reinterpret_cast<const char*>(bytes), offset + icmpSize);
    str = str.substr(offset, icmpSize);
    stringstream stream(str);

    stream >> icmpHeader.icmp_type;
    stream >> icmpHeader.icmp_code;
    stream.read(reinterpret_cast<char*>(&icmpHeader.icmp_sum), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&icmpHeader.icmp_rest), sizeof(uint32_t));
}

bool Icmp::isHeaderInvalid() {
    //  TODO
    return false;
}

QString Icmp::getFullData() {
    QString s =
        "\nProtocol:\tICMP\nType:\t" + QString::number(static_cast<int>(icmpHeader.icmp_type)) +
        "\nCode:\t" + QString::number(static_cast<int>(icmpHeader.icmp_code)) +
        "\nChecksum:\t" + QString::number(ntohs(icmpHeader.icmp_sum)) +
        "\nOptions:\t" + QString::number(ntohs(icmpHeader.icmp_rest));

    return s;
}
