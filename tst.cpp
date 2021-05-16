#include "tst.h"

Test::Test(QObject *parent) : QObject(parent)
{
    packet = new TestPacket();
    packet->number = 1;
    packet->timestamp = 100;
    packet->sourceIp = "192.168.1.1";
    packet->destIp = "192.168.1.1";
    packet->protocol = "TCP";
    packet->length = "128";
    packet->fullData = "Full data";

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->setInterval(1000);
    timer->start(1000);
}
