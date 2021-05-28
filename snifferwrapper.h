#ifndef SNIFFERWRAPPER_H
#define SNIFFERWRAPPER_H

#include <QObject>
#include <QThread>
#include <qqml.h>

#include <sniffer.h>

class SnifferWrapper : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Sniffer *sniffer;
    QThread thread;
public:
    explicit SnifferWrapper(QObject *parent = nullptr);
    Q_INVOKABLE void startCapture(int c);
    Q_INVOKABLE void stopCapture();
    Q_INVOKABLE QVariantMap getDevs();
    Q_INVOKABLE void setDev(QString d);
    Q_INVOKABLE bool initPcap();
    Q_INVOKABLE void closeHandle();
signals:
    void packetDeserialized(const Packet packet);
};

#endif // SNIFFERWRAPPER_H
