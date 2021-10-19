#ifndef FACTORY_H
#define FACTORY_H

#include <protocols/icmp.h>
#include <protocols/tcp.h>
#include <protocols/udp.h>
#include <protocols/unknowntransport.h>

#include <protocols/basetransport.hpp>
#include <QObject>
#include <iostream>

class Factory : public QObject {
  Q_OBJECT
 public:
  explicit Factory(QObject* parent = nullptr) {}

  static BaseTransport* makeTransport(int protocol) {
    BaseTransport* transport;
    switch (protocol) {
      case 1:
        transport = new Icmp();
        break;
      case 6:
        transport = new Tcp();
        break;
      case 17:
        transport = new Udp();
        break;
      default:
        transport = new UnknownTransport();
        break;
    }
    return transport;
  }

 signals:
};

#endif  // FACTORY_H
