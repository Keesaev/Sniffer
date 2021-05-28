#include "datalink.h"

DataLink::DataLink(QObject *parent) : QObject(parent)
{

}

void DataLink::deserializeHeader(const u_char *bytes){
    string str(reinterpret_cast<const char*>(bytes), ethernetHeaderSize);
    stringstream stream(str);

    for(int i = 0; i < 6; i++){
        stream >> ethernetHeader.ether_dhost[i];
    }

    for(int i = 0; i < 6; i++){
        stream >> ethernetHeader.ether_shost[i];
    }
    // stringstream не умеет читать u_short, перегрузка >> не помогает, поэтому так:
    stream >> reinterpret_cast<char*>(&ethernetHeader.ether_type), sizeof(bit16);
}

QString DataLink::getFullData(){
    QString s =
        "Ethernet II\n\tSource: " + getMac(ethernetHeader.ether_shost) +
        "\n\tDestination: " + getMac(ethernetHeader.ether_dhost) +
        "\n\tType: " + QString::number(ethernetHeader.ether_type);
    return s;
}

QString DataLink::getMac(const bit8 addr[]){
    QString s = "";
    for(int i = 0; i < 6; i++){
        s += byteToHexString(addr[i]) + ":";
    }
    s[s.length() - 1] = ' ';
    return s;
}

QString DataLink::byteToHexString(unsigned char a){
    int b = a / 16;
    int c = a % 16;

    return (getSingleHexRegister(b) + getSingleHexRegister(c));
}

QString DataLink::getSingleHexRegister(int b){
    QString res = "";
        if(b > 9){
            map<int, QString>::iterator f = hexLetters.find(b);
            if(f != hexLetters.end()){
                res = f->second;
            }
            else{
                res = "0";
            }
        }
        else{
            res = (char)(48 + b);
        }
        return res;
}
