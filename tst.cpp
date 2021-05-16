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
    QVariantMap m1 = {{"a", "b"}, {"a", "b"}, {"a", "b"}, {"a", "b"}};
    packet->dataLinkFullData = m1;
    packet->networkFullData = m1;
    packet->transportFullData = m1;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->setInterval(1000);
    timer->start(1000);
}
