#include "transport_factory.h"

#include "icmp.h"
#include "tcp.h"
#include "udp.h"
#include "unknown_transport.h"

std::unique_ptr<BaseTransport> TransportFactory::makeTransport(int protocol) {
  switch (protocol) {
    case 1:
      return std::make_unique<Icmp>();
    case 6:
      return std::make_unique<Tcp>();
    case 17:
      return std::make_unique<Udp>();
    default:
      return std::make_unique<UnknownTransport>();
  }
}
