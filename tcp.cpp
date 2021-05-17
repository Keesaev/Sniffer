#include "tcp.h"

Tcp::Tcp()
{

}

void Tcp::deserializeHeader(const u_char *bytes, int offset){
    string str(reinterpret_cast<const char*>(bytes), offset + tcpMaxHeaderSize);
    str = str.substr(offset, tcpMaxHeaderSize);
    stringstream stream(str);

    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_sport), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_dport), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_seqn), sizeof(bit32));
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_ack), sizeof(bit32));
    stream >> tcpHeader.tcp_offx2 >> tcpHeader.tcp_flags;
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_win), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_sum), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&tcpHeader.tcp_urp), sizeof(bit16));
}

bool Tcp::isHeaderInvalid() {
    unsigned int size_tcp = getOffset()*4;
    if((int)size_tcp < tcpMinHeaderSize || (int)size_tcp > tcpMaxHeaderSize)
        return true;
    else
        return false;
}

QString Tcp::getFullData(){
    QString s =
        "\nProtocol:\tTCP\nSource port:\t" + QString::number(htons(tcpHeader.tcp_sport)) +
        "\nDestination port:\t" + QString::number(htons(tcpHeader.tcp_dport)) +
        "\nSequence number:\t" + QString::number(htonl(tcpHeader.tcp_seqn)) +
        "\nAcknowledgment Number:\t" + QString::number(htonl(tcpHeader.tcp_ack)) +
        "\nData offset:\t" + QString::number(getOffset()) +
        "\nFlags:\t" + getFlags() +
        "\nWindow size:\t" + QString::number(htons(tcpHeader.tcp_win)) +
        "\nChecksum:\t" + QString::number(htons(tcpHeader.tcp_sum)) +
        "\nUrgent Point:\t" + QString::number(htons(tcpHeader.tcp_urp));
    return s;
}

int Tcp::getOffset(){
    return ((tcpHeader.tcp_offx2) >> 4);
}

// https://en.wikipedia.org/wiki/Transmission_Control_Protocol
// https://networkguru.ru/protokol-transportnogo-urovnia-tcp-chto-nuzhno-znat/
QString Tcp::getFlags(){
    QString s = "";
    if(tcpHeader.tcp_offx2 & 1)
        s += "NC (Nonce Sum)\n";
    for(auto i : flags){
        if(tcpHeader.tcp_flags & i.first)
            s += i.second;
    }
    return s;
}
