#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <Protocols/basetransport.h>
#include <Protocols/icmp.h>
#include <Protocols/tcp.h>
#include <Protocols/udp.h>
#include <Protocols/unknowntransport.h>

#include <iostream>

class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = nullptr);

    static BaseTransport* makeTransport(int protocol);

signals:

};

#endif // FACTORY_H
