#include "snifferwrapper.h"

SnifferWrapper::SnifferWrapper(QObject *parent) : QObject(parent)
{
    sniffer = new Sniffer();
    connect(sniffer, &Sniffer::packetDeserialized, this, &SnifferWrapper::packetDeserialized);
    connect(&thread, &QThread::started, sniffer, &Sniffer::startLoopingCapture);
}

void SnifferWrapper::startCapture(int c){
    sniffer->moveToThread(&thread);
    sniffer->setMaxPacket(c);
    thread.start();
}

void SnifferWrapper::stopCapture(){
    sniffer->stopCapture();
    thread.terminate();
}

void SnifferWrapper::setDev(QString d){
    sniffer->setDev(d);
}

bool SnifferWrapper::initPcap(){
    return sniffer->initPcap();
}

QVariantMap SnifferWrapper::getDevs(){
    return sniffer->getDevs();
}

void SnifferWrapper::closeHandle(){
    sniffer->closeHandle();
}
