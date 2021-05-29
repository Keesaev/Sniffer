#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{

}

QString Network::getFullData(){
    QString s =
        "\nIPv4\n\tVersion: " + QString::number(getVersion()) +
        "\n\tInternet Header Length: " + QString::number(getHeaderSize()) +
        "\n\tDifferenciated services code point: " + getDiffServ() +
        "\n\tExplicit Congestion Notification: " + getECN() +
        "\n\tTotal length: " + QString::number(ntohs(ipHeader.ip_len)) +
        "\n\tIdentification: " + QString::number(ntohs(ipHeader.ip_id)) +
        "\n\tFlags: " + getFlags() +
        "\n\tFragment offset: " + QString::number(getOffset()) +
        "\n\tTime to live: " + QString::number(static_cast<int>(ipHeader.ip_ttl)) +
        "\n\tProtocol: " + QString::number(getProtocol()) + tr("(") + getProtocolName() + tr(")") +
        "\n\tHeader checksum: " + QString::number(ntohs(ipHeader.ip_sum)) +
        "\n\tSource: " + getAddress(ipHeader.ip_src) +
        "\n\tDestination: " + getAddress(ipHeader.ip_dst);
    return s;
}

void Network::deserializeHeader(const u_char *bytes){
    // Читаем последовательность длиной ethernetSize + ipMaxSize
    string str(reinterpret_cast<const char*>(bytes), ethernetHeaderSize + ipMaxHeaderSize);
    str = str.substr(ethernetHeaderSize, ipMaxHeaderSize);
    stringstream stream(str);

    stream >> ipHeader.ip_vhl;
    stream >> ipHeader.ip_tos;
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_len), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_id), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_off), sizeof(bit16));
    stream >> ipHeader.ip_ttl;
    stream >> ipHeader.ip_p;
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_sum), sizeof(bit16));
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_src), sizeof(in_addr));
    stream.read(reinterpret_cast<char*>(&ipHeader.ip_dst), sizeof(in_addr));
}

bool Network::isHeaderEmpty(){ // TODO
    unsigned int size_ip = getHeaderSize() * 4;
    if(size_ip < ipMinHeaderSize)
        return true;
    else{
        return false;
    }
}

int Network::getProtocol(){
    return ipHeader.ip_p;
}

QString Network::getProtocolName(){
    int p = static_cast<int>(ipHeader.ip_p);
    QString s = "";

    map<int, QString>::iterator res = transportProts.find(p);
    if(res != transportProts.end())
        s = res->second;
    else if(p >= 144 && p <= 252)
        s = "Unassigned";
    else
        s = "Unknown";
    return s;
}

// Читаем левые 4 бита поля ip_vhl
int Network::getHeaderSize(){
    return (((ipHeader).ip_vhl) & 0x0f) * 4;
}

QString Network::getSourceIp(){
    return getAddress(ipHeader.ip_src);
}

QString Network::getDestIp(){
    return getAddress(ipHeader.ip_dst);
}

QString Network::getAddress(in_addr addr){
    char cAddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr), cAddr, INET_ADDRSTRLEN);
    return cAddr;
}

QString Network::getECN(){
    int e = ipHeader.ip_tos & 3;
    QString s = "Decimal value: " + QString::number(e);

    map<int, QString>::iterator res = ecn.find(e);
    if(res != ecn.end())
        s += " (" + res->second + ")";

    return s;
}

QString Network::getDiffServ(){
    int ds = ipHeader.ip_tos >> 2;
    QString s = "Decimal value: " + QString::number(ds);

    map<int, QString>::iterator res = diffServ.find(ds);
    if(res != diffServ.end())
        s += " (DSCP: " + res->second + ")";

    return s;
}

// https://www.pearsonitcertification.com/articles/article.aspx?p=1843887
QString Network::getFlags(){
    QString s = "";
    int a = ntohs(ipHeader.ip_off);
    bool df = (a >> 14) & 1;
    bool mf = (a >> 13) & 1;

    s += df ? "Don't fragment " : "";
    s += mf ? "More fragments" : "";

    if(s.isEmpty())
        s = "Not set";

    return s;
}

int Network::getVersion(){       // Читаем правые 4 бита поля ip_vhl
    return ((ipHeader.ip_vhl) >> 4);
}
int Network::getOffset(){        // Берем всё кроме левых 3 битов в ip_off
    return (ntohs(ipHeader.ip_off) & 8191);
}


