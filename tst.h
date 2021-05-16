#ifndef TST_H
#define TST_H

#include <QObject>
#include <string>
#include <vector>
#include <qqml.h>
#include <testpacket.h>

#include <QTimer>
#include <QTime>

#include <QDebug>

using namespace std;

class Test : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Test(QObject *parent = nullptr);
    Q_INVOKABLE QVariantMap getList(){
        return map;
    }
    TestPacket *packet;
    QTimer *timer;
    QVariantMap map = {{"a", "b"}, {"c", "d"}, {"e", "f"}};
public slots:
    void onTimer(){
        emit packetDeserialized(packet);
    }
signals:
    void packetDeserialized(TestPacket *packet);
};

#endif // TST_H
